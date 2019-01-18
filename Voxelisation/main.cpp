#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <list>
#include <fstream>
#include <string>
#include <vector>
#include "prog.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/base/Common.h"
#include "DGtal/shapes/Mesh.h"
#include "DGtal/shapes/MeshVoxelizer.h"
#include "DGtal/io/boards/Board3D.h"
#include "DGtal/io/writers/MeshWriter.h"
#include "DGtal/io/readers/VolReader.h"
#include "DGtal/io/Display3D.h"
#include "DGtal/io/viewers/Viewer3D.h"
#include "DGtal/io/DrawWithDisplay3DModifier.h"
#include "DGtal/images/ImageSelector.h"
#include "DGtal/images/imagesSetsUtils/SetFromImage.h"
using namespace std;
using namespace std::chrono;
using namespace DGtal;
using namespace DGtal::Z3i;
float scale = 100;

int main(int argc, char** argv)
{
  //camel(argc,argv);
  if (argc<3) {
    cout << "./voxelisation mesh.off scale" << endl;
  }
  read(argv[1]);
  scale = atoi(argv[2]);
  vector<RealPoint> Points;
  vector<array<int,3>> Faces;
  QApplication application(argc,argv);
  Viewer3D<> viewer;
  viewer.show();
  char* nom = (char*)malloc(100);
  sprintf(nom,"../../Mesh/");
  sprintf(nom+11,argv[1]);
  sprintf(nom+11+strlen(argv[1])-4,argv[2]);
  sprintf(nom+11+strlen(argv[1])-4+strlen(argv[2]),".txt");
  ofstream Vol(nom);

  //viewer.addLine(RealPoint(p1[0],p1[1],p1[2]),RealPoint(p2[0],p2[1],p2[2]), 1);

  Mesh<RealPoint> aMesh(true);
  float* res;
  int* id;
  int i = 0;
  double x,y,z;
  char char_array[255];
  string ligne;
  ifstream Pfile ("./Points.txt");
  while (getline(Pfile, ligne)) {
    if(i%3 == 0){
      QString winOpacity(ligne.c_str());
      x = winOpacity.toDouble()*scale;
    } else if(i%3==1) {
      QString winOpacity(ligne.c_str());
      y= winOpacity.toDouble()*scale;
    } else {
      QString winOpacity(ligne.c_str());
      z= winOpacity.toDouble()*scale;
      Points.push_back(RealPoint(x,y,z));
    }
    i++;
  }
  Pfile.close();


  ifstream Ffile ("./Faces.txt");
  while (getline(Ffile, ligne)) {
    strcpy(char_array, ligne.c_str());
    id = extractInt(char_array,4);
    array<int,3> tab = {id[1], id[2], id[3]};
    Faces.push_back(tab);

  }
  Ffile.close();

  for (auto point = Points.begin(); point != Points.end(); ++point) aMesh.addVertex(*point);

  array<double,3> p1 = {0,0,0};
/*
//intersection d'un rayon et du Mesh
// debut
  list<FacePoint> maListe = listFaces(Faces,Points,p1,{p2[0]-p1[0],p2[1]-p1[1],p2[2]-p1[2]});
  for(auto it = maListe.begin(); it != maListe.end(); ++it){
    aMesh.addTriangularFace((*it).id1, (*it).id2, (*it).id3, Color(255,255,255,255));
    viewer.addBall((*it).point,0.001*scale);

  }
  cout << maListe.size() << " points trouves" << endl;
// fin
*/
  for (auto face = Faces.begin(); face != Faces.end(); ++face) aMesh.addTriangularFace((*face)[0], (*face)[1], (*face)[2], Color(0,0,0,50));
  array<RealPoint,2> rayon;

  /*
  array<double,6> B = bords(Points);
  rayon = displayRay(B,p1,p2);
  cout << rayon[0][0] << "\t" << rayon[0][1] << "\t" << rayon[0][2] << "\n";
  cout << rayon[1][0] << "\t" << rayon[1][1] << "\t" << rayon[1][2] << "\n";
  viewer.addLine(rayon[0],rayon[1],1);
*/

  //
  //
  // Voxelisation
  high_resolution_clock::time_point t1 = high_resolution_clock::now();


  array<double,3> v = {0,1,0};
  vector<array<double,3>>rayons = rays(bords(Points),p1,v,1);
  /*
  cout << rayons.size() << endl;
  for (auto &ray : rayons) {
    //viewer.addBall(RealPoint((*ray)[0], (*ray)[1], (*ray)[2]),0.01*scale);
    rayon = displayRay(bords(Points), ray,{ray[0]+v[0], ray[1]+v[1], ray[2]+v[2]});
    viewer.addLine(rayon[0],rayon[1],1);
  }

  */


  vector<array<double,3>> voxels = parityCount(Faces,Points);
  high_resolution_clock::time_point t2 = high_resolution_clock::now();
  auto duration = duration_cast<seconds>( t2 - t1 ).count();
  cout << voxels.size() << " voxels" <<  endl;
  cout << "executed in " << duration/60 << " min "<< duration % 60 << " s" << endl;
  for (auto voxel = voxels.begin(); voxel != voxels.end(); ++voxel) {
    viewer.addCube(RealPoint((*voxel)[0], (*voxel)[1], (*voxel)[2]),1);
    Vol << (*voxel)[0]<< " " << (*voxel)[1] << " " << (*voxel)[2] << endl;
  }
  //
  //
  //

  Vol.close();
  viewer.setLineColor(Color(0,0,0,50));
  viewer << aMesh;
  viewer << Viewer3D<>::updateDisplay;

  application.exec();

  return 0;
}


array<RealPoint,2> displayRay(array<double,6> bord, array<double,3> p1, array<double,3> p2){
  array<double,3> v = {p2[0]-p1[0],p2[1]-p1[1],p2[2]-p1[2]};
  float ajust = 0;//scale / 10;
  if (v[1] != 0) {
    return {intersection({0,1,0,bord[1]-ajust},p1,v),intersection({0,1,0,bord[4]+ajust},p1,v)};
  } else if (v[0] != 0){
    return {intersection({1,0,0,bord[0]-ajust},p1,v),intersection({1,0,0,bord[3]+ajust},p1,v)};
  } else {
    return {intersection({0,0,1,bord[2]-ajust},p1,v),intersection({0,0,1,bord[5]+ajust},p1,v)};
  }
}

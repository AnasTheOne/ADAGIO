#include <array>
#include <vector>
#include "DGtal/helpers/StdDefs.h"
#include "prog.h"
using namespace std;
using namespace DGtal;
using namespace DGtal::Z3i;

vector<array<double,3>> rays(array<double,6> mesBords,array<double,3> P,array<double,3> V,double alpha){///Plan normal
  /*
  vector<array<double,3>> rays;
  double x0 = P[0];double y0 = P[1];double z0 = P[2];
  double xmi,xma,ymi,yma,zmi,zma;
  xmi = mesBords[0]; xma = mesBords[3];ymi = mesBords[1]; yma = mesBords[4];zmi = mesBords[2];zma = mesBords[5];
  double d = produitCart(V,{P[0],P[1],P[2]});
  array<double,4> plan = {V[0],V[1],V[2],d};
  if( V[2] != 0){
    double rx0 = (x0 - ((int) x0/alpha )*alpha); double ry0 = (y0 - ((int) y0/alpha )*alpha);
    for (double x = ((int) ((xmi - rx0 )/alpha) ) * alpha + rx0; x < xma; x += alpha ) {
      for (double y = ((int) ((ymi - rx0 )/alpha) ) * alpha + ry0; y < yma; y += alpha ) {
        //rays.push_back({x,y,z0});
        rays.push_back({x,y,d-produitCart(V,{x,y,0})});
      }
    }
    return rays;
  } else {
    double rx0 = (x0 - ((int) x0/alpha )*alpha); double rz0 = (z0 - ((int) z0/alpha )*alpha);
    for (double x = ((int) ((xmi - rx0 )/alpha) ) * alpha + rx0; x < xma; x += alpha ) {
      for (double z = ((int) ((zmi - rz0 )/alpha) ) * alpha + rz0; z < zma; z += alpha ) {
        rays.push_back({x,d-produitCart(V,{x,0,z}),z});
      }
    }
    return rays;
  }

*/
  vector<array<double,3>> rays;
  double x0 = P[0];double y0 = P[1];double z0 = P[2];
  double xmi,xma,ymi,yma,zmi,zma;
  double d = produitCart(V,{P[0],P[1],P[2]});
  xmi = mesBords[0]; xma = mesBords[3];ymi = mesBords[1]; yma = mesBords[4];zmi = mesBords[2];zma = mesBords[5];
  //if(x0>xma || x0 < xmi || y0 > yma || y0 < ymi || z0 > zma || z0 < zma){cout << "Oups" << endl;} else {}
  if( V[0]!=0){
    double ry0 = (y0 - ((int) y0/alpha )*alpha); double rz0 = (z0 - ((int) z0/alpha )*alpha);
    for (double y = ((int) ((ymi - ry0 )/alpha) ) * alpha + ry0; y < yma; y += alpha ) {
      for (double z = ((int) ((zmi - rz0 )/alpha) ) * alpha + rz0; z < zma; z += alpha ) {
        rays.push_back({d-produitCart(V,{0,y,z}),y,z});
      }
    }
    return rays;
  } else if(V[1]!=0) {
    double rx0 = (x0 - ((int) x0/alpha )*alpha); double rz0 = (z0 - ((int) z0/alpha )*alpha);
    for (double x = ((int) ((xmi - rx0 )/alpha) ) * alpha + rx0; x < xma; x += alpha ) {
      for (double z = ((int) ((zmi - rz0 )/alpha) ) * alpha + rz0; z < zma; z += alpha ) {
        rays.push_back({x,d-produitCart(V,{x,0,z}),z});
      }
    }
    return rays;
  } else {
    double rx0 = (x0 - ((int) x0/alpha )*alpha); double ry0 = (y0 - ((int) y0/alpha )*alpha);
    for (double x = ((int) ((xmi - rx0 )/alpha) ) * alpha + rx0; x < xma; x += alpha ) {
      for (double y = ((int) ((ymi - ry0 )/alpha) ) * alpha + ry0; y < yma; y += alpha ) {
        rays.push_back({x,y,d-produitCart(V,{x,y,0})});
      }
    }
    return rays;
  }

}

bool compareFaceX(FacePoint& face1, FacePoint& face2){
    return ( face1.point[0] < face2.point[0] );
}

bool compareFaceY(FacePoint& face1, FacePoint& face2){
    return ( face1.point[1] < face2.point[1] );
}

bool compareFaceZ(FacePoint& face1, FacePoint& face2){
  return ( face1.point[2] < face2.point[2] );
}

vector<array<double,3>> intBetweenPoints(array<double,3> p1,array<double,3> p2){
  array<double,3> v = {p2[0]-p1[0],p2[1]-p1[1],p2[2]-p1[2]};
  vector<array<double,3>> Points;
  double x0 = 0;double y0 = 0;double z0 = 0;
  if(p1[0] == (int)p1[0]) x0 = p1[0]; else if(p1[0] < 0) x0 = (int) p1[0];else x0 = (int) p1[0] + 1;
  if(p1[1] == (int)p1[1]) y0 = p1[1]; else if(p1[1] < 0) y0 = (int) p1[1];else y0 = (int) p1[1] + 1;
  if(p1[2] == (int)p1[2]) z0 = p1[2]; else if(p1[2] < 0) z0 = (int) p1[2];else z0 = (int) p1[2] + 1;
  if(v[0] != 0) {
    for (double x = x0; x <= p2[0]; x++) {
      double y = p1[1] + (x-p1[0])/v[0]*v[1];
      double z = p1[2] + (x-p1[0])/v[0]*v[2];
      if(y == (int)y && z == (int)z) Points.push_back({x,y,z});
    }
  } else if(v[1] != 0) {
    for (double y = y0; y <= p2[1]; y++) {
      double x = p1[0] + (y-p1[1])/v[1]*v[0];
      double z = p1[2] + (y-p1[1])/v[1]*v[2];
      if(x == (int)x && z == (int)z) Points.push_back({x,y,z});
    }
  } else {
    for (double z = z0; z <= p2[2]; z++) {
      double x = p1[0] + (z-p1[2])/v[2]*v[0];
      double y = p1[1] + (z-p1[2])/v[2]*v[1];
      if(x == (int)x && y == (int)y) Points.push_back({x,y,z});
    }
  }
  return Points;
}

vector<array<double,3>> parityCount(vector<array<int,3>> Faces,vector<RealPoint> Points){
  list<FacePoint> maListe; vector<array<double,3>> voxelsCoords;
  vector<RealPoint> listePoints;
  array<double,6> mesBords = bords(Points);
  array<double,3> V = {0,1,0};// problem avec V = {1,0,0};
  array<double,3> P0 = {0,0,0};
  vector<array<double,3>> rayons = rays(mesBords,P0,V,1);
  unsigned long nbrRays = rayons.size();
  unsigned long taille;
  int i = 1;
  RealPoint p1,p2;
  for (auto &rayon : rayons) {
    maListe = listFaces(Faces,Points, rayon,V);
    if(V[2] != 0) maListe.sort(compareFaceZ);
    else if(V[1] != 0) maListe.sort(compareFaceY);
    else maListe.sort(compareFaceX);
    for (auto &it : maListe) { listePoints.push_back(it.point); }
    taille = listePoints.size();
    cout << "(" << i << "\t/ " << nbrRays << ")\n";
    if( taille%2 == 1) cout << "un probleme ici" << endl;
    else if(taille!=0) for (int j = 0; j < taille/2; ++j){
      //cout << (listePoints[2*j])[0] << "\t\t" << (listePoints[2*j])[1] << "\t\t" << (listePoints[2*j])[2] << "\n";
      //cout << (listePoints[2*j+1])[0] << "\t\t" << (listePoints[2*j +1])[1] << "\t\t" << (listePoints[2*j+1])[2] << "\n";
      p1 = listePoints[2*j]; p2 = listePoints[2*j+1];
      vector<array<double,3>> pointsEntiers = intBetweenPoints({p1[0],p1[1],p1[2]},{p2[0],p2[1],p2[2]});
      for (auto &pointsEntier : pointsEntiers) voxelsCoords.push_back(pointsEntier);
    }
    maListe.clear(); listePoints.clear();

    i++;
  }
  cout << nbrRays << " rays" << endl;
  return voxelsCoords;
}

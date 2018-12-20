#include <iostream>
#include <list>
#include <fstream>
#include <string>
#include <array>
//#include <bits/stdc++.h>
#include "DGtal/helpers/StdDefs.h"
#include "prog.h"
using namespace std;
using namespace DGtal;
using namespace DGtal::Z3i;

int* extractInt(char* line,int N){
  int i = 0;
  int res = 0;
  int* ret = (int*)malloc(sizeof(int)*N);
  for (size_t j = 0; j < N; j++) {
    while (line[i]!=' ' && line[i]!=0  && line[i]!='\n' ) {
      res = res * 10+(line[i]-48);
      i++;
    }
    i++;
    ret[j] = res;
    res=0;
  }
  return ret;
}

float* extractFloat(char* line){

  int coeff = 1;
  std::string coord (line);
  std::string::size_type sz1;
  std::string::size_type sz2;
  float x = std::stof (coord,&sz1);
  float y = std::stof (coord.substr(sz1),&sz2);
  float z = std::stof (coord.substr(sz1+sz2));
  float* res = (float*) malloc(sizeof(float)*3);
  res[0] = x*coeff;
  res[1] = y*coeff;
  res[2] = z*coeff;
  return res;
}


array<double,3> produitVect(array<double,3> vect1,array<double,3> vect2){
  return {vect1[1]*vect2[2]-vect1[2]*vect2[1],vect1[2]*vect2[0]-vect1[0]*vect2[2],vect1[0]*vect2[1]-vect1[1]*vect2[0]};
}

double produitCart(array<double,3> vect1,array<double,3> vect2){
  return vect1[0]*vect2[0]+vect1[1]*vect2[1]+vect1[2]*vect2[2];
}

double norm(array<double,3> vect){
  return produitCart(vect,vect);
}

double area(RealPoint P1, RealPoint P2, RealPoint P3)
{
  array<double,3> P1P2 = {P2[0]-P1[0],P2[1]-P1[1],P2[2]-P1[2]};
  array<double,3> P1P3 = {P3[0]-P1[0],P3[1]-P1[1],P3[2]-P1[2]};
  return norm(produitVect(P1P2,P1P3))/2.0;
}

bool isInside(RealPoint P1, RealPoint P2, RealPoint P3, RealPoint P){
  array<double,3> P1P2 = {P2[0]-P1[0],P2[1]-P1[1],P2[2]-P1[2]};
  array<double,3> P1P3 = {P3[0]-P1[0],P3[1]-P1[1],P3[2]-P1[2]};
  array<double,3> P2P3 = {P3[0]-P2[0],P3[1]-P2[1],P3[2]-P2[2]};
  array<double,3> P3P1 = {P1[0]-P3[0],P1[1]-P3[1],P1[2]-P3[2]};
  array<double,3> P1P = {P[0]-P1[0],P[1]-P1[1],P[2]-P1[2]};
  array<double,3> P2P = {P[0]-P2[0],P[1]-P2[1],P[2]-P2[2]};
  array<double,3> P3P = {P[0]-P3[0],P[1]-P3[1],P[2]-P3[2]};
  array<double,3> n = produitVect(P1P2,P1P3);
  array<double,3> n1 = produitVect(P2P3,P2P);
  array<double,3> n2 = produitVect(P3P1,P3P);
  array<double,3> n3 = produitVect(P1P2,P1P);
  double alpha = produitCart(n,n1)/norm(n);
  double beta = produitCart(n,n2)/norm(n);
  double gamma = produitCart(n,n3)/norm(n);
  if(alpha >=0 and alpha <=1 and beta >=0 and beta <=1 and gamma >=0 and gamma <=1) return true;
  return false;

}

array<double,4> getPlan(RealPoint P1, RealPoint P2, RealPoint P3){
  array<double,3> P1P2 = {P2[0]-P1[0],P2[1]-P1[1],P2[2]-P1[2]};
  array<double,3> P1P3 = {P3[0]-P1[0],P3[1]-P1[1],P3[2]-P1[2]};
  array<double,3> produit = produitVect(P1P2,P1P3);
  double d = produitCart(produit,{P1[0],P1[1],P1[2]});
  return {produit[0],produit[1],produit[2],d};
}

RealPoint intersection(array<double,4> Plan, array<double,3> P, array<double,3> V){
  double a = Plan[0];double b = Plan[1];double c = Plan[2];double d = Plan[3];
  double det = (a*V[0]+b*V[1]+c*V[2]);
  if (det == 0) ;//cout << "plan parallel au vecteur" << '\n';
  else{
    double t = (d-(a*P[0]+b*P[1]+c*P[2]))/det;
    return RealPoint(P[0]+t*V[0],P[1]+t*V[1],P[2]+t*V[2]);
  }
}

list<FacePoint> listFaces(vector<array<int,3>> Faces,vector<RealPoint> Points,array<double,3> P, array<double,3> V){
  list<FacePoint> listDeFaces;
  FacePoint myFacePoint;
  for (auto face = Faces.begin(); face != Faces.end(); ++face){
    myFacePoint.id1 = (*face)[0];myFacePoint.id2 = (*face)[1];myFacePoint.id3 = (*face)[2];
    array<double,4> Plan =  getPlan(Points[myFacePoint.id1],Points[myFacePoint.id2],Points[myFacePoint.id3]);
    RealPoint PI = intersection(Plan,P,V);
    myFacePoint.point = PI;
    if(isInside(Points[myFacePoint.id1],Points[myFacePoint.id2],Points[myFacePoint.id3],myFacePoint.point)) listDeFaces.push_back(myFacePoint);
  }
  return listDeFaces;
}

array<double,6> bords(vector<RealPoint> Points){
  double minX,minY,minZ,maxX,maxY,maxZ;
  array<double,6> res;
  auto point = Points.begin();
  minX = (*point)[0]; minY = (*point)[1]; minZ = (*point)[2];
  maxX = (*point)[0]; maxY = (*point)[1]; maxZ = (*point)[2];
  ++point;
  for (; point != Points.end(); ++point){
    if ((*point)[0]<minX) minX = (*point)[0];
    if ((*point)[0]>maxX) maxX = (*point)[0];

    if ((*point)[1]<minY) minY = (*point)[1];
    if ((*point)[1]>maxY) maxY = (*point)[1];

    if ((*point)[2]<minZ) minZ = (*point)[2];
    if ((*point)[2]>maxZ) maxZ = (*point)[2];
  }
  res[0] = minX;res[1] = minY;res[2] = minZ;
  res[3] = maxX;res[4] = maxY;res[5] = maxZ;
  //cout << res[0] << "\t" << res[3] << "\t" << res[1] << "\t" << res[4] << "\t" << res[2] << "\t" << res[5] << "\n";
  return res;
}

double maxArray(array<double,6> monArray){
    double max = monArray[0];
    for(auto &elem : monArray){
        if(max < elem) max = elem;
    }
    return max;
}
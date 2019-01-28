//
// Created by anas on 11/01/19.
//

#ifndef MARCHINGCUBE_PROG_H
#define MARCHINGCUBE_PROG_H
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
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;
using namespace DGtal;
using namespace DGtal::Z3i;

int* extract(string line);
array<int,6> bords(vector<array<int,3>> Points);
array<int,4> bordsX(vector<array<int,3>> Points,int i);
array<int,2> bordsXY(vector<array<int,3>> Points,int i,int j);
array<int,6> bordsIntegral(vector<array<int,3>> Points,int i,int j,int k);
bool cherche3(vector<array<int,3>> Points, array<int,3> target);
bool cherche8(vector<array<int,8>> Points, array<int,8> target);
RealPoint IntersPoint(array<int,3> P1,array<int,3> P2,double alpha);
bool chercheGrille(array<array<int,3>,8> Points, array<int,3> target);

#endif //MARCHINGCUBE_PROG_H

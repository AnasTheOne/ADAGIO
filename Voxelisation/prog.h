#include <array>
#include <vector>
#include <list>
#include "DGtal/helpers/StdDefs.h"
using namespace std;
using namespace DGtal;
using namespace DGtal::Z3i;

struct FacePoint
{
    int id1;
    int id2;
    int id3;
    RealPoint point;
};


int affiche( int argc, char** argv );
int read(char* name);
int* extractInt(char* line,int N);
float* extractFloat(char* line);
void voxel(double x, double y, double z);
double produitCart(array<double,3> vect1,array<double,3> vect2);
array<double,3> produitVect(array<double,3> vect1,array<double,3> vect2);
list<FacePoint> listFaces(vector<array<int,3>> Faces,vector<RealPoint> Points,array<double,3> P, array<double,3> V);
array<double,6> bords(vector<RealPoint> Points);
vector<array<double,3>> parityCount(vector<array<int,3>> Faces,vector<RealPoint> Points);
array<RealPoint,2> displayRay(array<double,6> bord, array<double,3> p1, array<double,3> p2);
RealPoint intersection(array<double,4> Plan, array<double,3> P, array<double,3> V);
vector<array<double,3>> rays(array<double,6> mesBords,array<double,3> P,array<double,3> V,double alpha);
int camel(int argc, char** argv);
array<double,3> point(array<double,4> Plan, float coord, int axis);
vector<array<double,3>> intBetweenPoints(array<double,3> p1,array<double,3> p2);
double maxArray(array<double,6> monArray);

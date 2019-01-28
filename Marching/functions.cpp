#include "prog.h"

int* extract(string line){
    std::string coord (line);
    std::string::size_type sz1;
    std::string::size_type sz2;
    int x = std::stoi (coord,&sz1);
    int y = std::stoi (coord.substr(sz1),&sz2);
    int z = std::stoi (coord.substr(sz1+sz2));
    int* res = (int*) malloc(sizeof(int)*3);
    res[0] = x;
    res[1] = y;
    res[2] = z;
    return res;
}

double produitCart(array<double,3> vect1,array<double,3> vect2){
    return vect1[0]*vect2[0]+vect1[1]*vect2[1]+vect1[2]*vect2[2];
}

double norm(array<double,3> vect){
    return produitCart(vect,vect);
}

array<int,6> bords(vector<array<int,3>> Points){
    int minX,minY,minZ,maxX,maxY,maxZ;
    array<int,6> res;
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

array<int,4> bordsX(vector<array<int,3>> Points,int i){
    int minY,minZ,maxY,maxZ;
    array<int,4> res;
    auto point = Points.begin();
    minY = (*point)[1]; minZ = (*point)[2];
    maxY = (*point)[1]; maxZ = (*point)[2];
    ++point;
    for (; point != Points.end(); ++point){
        if ((*point)[0]==i){
            if ((*point)[1]<minY) minY = (*point)[1];
            if ((*point)[1]>maxY) maxY = (*point)[1];

            if ((*point)[2]<minZ) minZ = (*point)[2];
            if ((*point)[2]>maxZ) maxZ = (*point)[2];
        }
    }
    res[0] = minY;res[1] = minZ;
    res[2] = maxY;res[3] = maxZ;
    //cout << res[0] << "\t" << res[3] << "\t" << res[1] << "\t" << res[4] << "\t" << res[2] << "\t" << res[5] << "\n";
    return res;
}

array<int,2> bordsXY(vector<array<int,3>> Points,int i,int j){
    int minZ,maxZ;
    array<int,2> res;
    auto point = Points.begin();
    minZ = (*point)[2];
    maxZ = (*point)[2];
    ++point;
    for (; point != Points.end(); ++point){
        if ((*point)[0]==i && (*point)[1]==j ){

            if ((*point)[2]<minZ) minZ = (*point)[2];
            if ((*point)[2]>maxZ) maxZ = (*point)[2];
        }
    }
    res[0] = minZ;
    res[1] = maxZ;
    //cout << res[0] << "\t" << res[3] << "\t" << res[1] << "\t" << res[4] << "\t" << res[2] << "\t" << res[5] << "\n";
    return res;
}

bool cherche3(vector<array<int,3>> Points, array<int,3> target){
    for(auto &point:Points){
        if(point == target) return true;
    }
    return false;
}

bool chercheGrille(array<array<int,3>,8> Points, array<int,3> target){
    for(auto &point:Points){
        if(point == target) return true;
    }
    return false;
}

bool cherche8(vector<array<int,8>> Points, array<int,8> target){
    for(auto &point:Points){
        if(point == target) return true;
    }
    return false;
}

RealPoint IntersPoint(array<int,3> P1,array<int,3> P2,double alpha){
    return RealPoint(P1[0]+alpha*(P2[0]-P1[0]),P1[1]+alpha*(P2[1]-P1[1]),P1[2]+alpha*(P2[2]-P1[2]));
    /*
    if(norm({(double) P1[0],(double) P1[1],(double) P1[2]})==norm({(double) P2[0],(double) P2[1],(double) P2[2]})) return {(double) P1[0],(double) P1[1],(double) P1[2]};
    else {
        double mu = (alpha -norm({(double) P1[0],(double) P1[1],(double) P1[2]}))/(norm({(double) P2[0],(double) P2[1],(double) P2[2]})-norm({(double) P1[0],(double) P1[1],(double) P1[2]}));
        return RealPoint(P1[0]+mu*(P2[0]-P1[0]),P1[1]+mu*(P2[1]-P1[1]),P1[2]+mu*(P2[2]-P1[2]));
    }*/
}


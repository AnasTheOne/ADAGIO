#include <fstream>
#include <vector>
#include <algorithm>
#include <set>
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int* extract(string line,int res[3]){
    std::string coord (line);
    std::string::size_type sz1;
    std::string::size_type sz2;
    int x = std::stoi (coord,&sz1);
    int y = std::stoi (coord.substr(sz1),&sz2);
    int z = std::stoi (coord.substr(sz1+sz2));
    res[0] = x;
    res[1] = y;
    res[2] = z;
    return res;
}

int compar(array<int,3> Point1,array<int,3> Point2){
    if(Point1[0]<Point2[0]) return 1;
    if(Point1[0]>Point2[0]) return -1;
    if(Point1[1]<Point2[1]) return 1;
    if(Point1[1]>Point2[1]) return -1;
    if(Point1[2]<Point2[2]) return 1;
    if(Point1[2]>Point2[2]) return -1;
    return 0;
}

bool comparer(array<int,3> Point1,array<int,3> Point2){
    if(Point1[0]<Point2[0]) return true;
    if(Point1[0]>Point2[0]) return false;
    if(Point1[1]<Point2[1]) return true;
    if(Point1[1]>Point2[1]) return false;
    if(Point1[2]<Point2[2]) return true;
    if(Point1[2]>Point2[2]) return false;
    return false;
}

int main(int argc, char** argv)
{
    if(argc < 3) {
        cout << "./verify "<< "file1.txt" << " file2.txt" <<endl;
        return -1;
    }

    string ligne;
    char* nom1 = (char*) malloc(100);
    char* nom2 = (char*) malloc(100);
    sprintf(nom1,"../../Mesh/");
    sprintf(nom2,"../../Mesh/");
    sprintf(nom1+11,argv[1]);
    sprintf(nom2+11,argv[2]);
    cout << nom1 << "\t" << nom2 << endl;
    ifstream file1(nom1);
    ifstream file2(nom2);
    vector<array<int,3>> Voxels1,Voxels2,notIn1,notIn2;
    int id[3];

    if(!file1.fail() && !file2.fail() ){
        while (getline(file1,ligne)){
            extract(ligne,id);

            Voxels1.push_back({id[0],id[1],id[2]});
        }
        while (getline(file2,ligne)){
            extract(ligne,id);
            Voxels2.push_back({id[0],id[1],id[2]});
        }
        sort(Voxels1.begin(), Voxels1.end(), comparer);
        sort(Voxels2.begin(), Voxels2.end(), comparer);
        long n1 = Voxels1.size();
        long n2 = Voxels2.size();
        long i = 0;
        long j = 0;
        while(i< n1 && j < n2){
            int res = compar(Voxels1[i],Voxels2[j]);
            if(res == 1){
                notIn2.push_back(Voxels1[i]);
                i++;
            } else if(res == -1){
                notIn1.push_back(Voxels2[i]);
                j++;
            } else {
                i++;j++;
            }
        }
        if(i++!=n1) notIn2.push_back(Voxels1[i]);
        if(j++!=n2) notIn1.push_back(Voxels2[j]);
        cout << "Not in "<<argv[1]<<": \n";
        for(auto &point:notIn1){
            cout << point[0] << "\t" << point[1] << "\t"<< point[2] << "\n";
        }
        cout << "Not in "<<argv[2]<<": \n";
        for(auto &point:notIn2){
            cout << point[0] << "\t" << point[1] << "\t"<< point[2] << "\n";
        }

    } else {
        cout << "Probleme d'ouverture de fichier\n";
        if(file1.fail() && file2.fail());
        else if(file1.fail()) file2.close();
        else if(file2.fail()) file1.close();
        return -1;
    }
    file1.close();
    file2.close();
}
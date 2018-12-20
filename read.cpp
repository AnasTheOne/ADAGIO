#include <iostream>
#include <fstream>
#include <string>
//#include <bits/stdc++.h>
#include "prog.h"

using namespace std;


int read(char* name) {
  string repertory = "../Mesh/";
  float* res;
  int* stop ;
  char char_array[255];
  string line = "O";

  string buf(repertory);
  repertory.append(name);

  ifstream file (repertory);
  ofstream Pfile ("./Points.txt");
  ofstream Ffile ("./Faces.txt");
  if (file.is_open())
  {
    for (size_t i = 0; i < 10  && (58 < line[0] || line[0] > 47); i++ && getline (file,line)) {
      strcpy(char_array, line.c_str());
      stop = extractInt(char_array,3);
    }

    strcpy(char_array, line.c_str());
    res = extractFloat(char_array);
    for (size_t x = 0; x < 3; x++) {
      Pfile << res[x] << '\n';
    }
    for (size_t i = 0; i < stop[0]-1 && getline (file,line); i++) {
      strcpy(char_array, line.c_str());
      res = extractFloat(char_array);
      for (size_t x = 0; x < 3; x++) {
        Pfile << res[x] << '\n';
      }
    }
    for (size_t i = 0; i < stop[1] && getline (file,line); i++) {
      Ffile << line << '\n';
    }
    file.close();
    Pfile.close();
    Ffile.close();
  }

  else cout << "Unable to open file";

  return 0;
}

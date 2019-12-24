#include <iostream>
#include <cstring>
#include "header.hpp"
using namespace std;

void mprint (int** a, int i, int j) {
        cout << endl;
    for (int i0 = 0; i0 < i; i0++) {
        for (int j0 = 0; j0 < j; j0++) {
            cout << a[i0][j0] << " ";
        }
        cout << endl;
    }
}

void enterthematrix (int** & M, int i, int j, string dat) {

    M = new int*[i];
    for (int c = 0; c < i; c++)
        M[c] = new int[j];
    
    int n = 0;
    //todo: fix crashes
  for (int i0 = 0; i0 < i; i0++) {
      for (int j0 = 0 ; j0 < j; j0++) {
          string t = "0";
          while (dat[n] != '.') { t = t+dat[n], n++;};
          M[i0][j0] = stoi(t); if (n < dat.length()) {n++;}; 
      }
  }
//  cout << endl << "Your matrix is: " << endl;
  mprint(M,i,j);


    // gauss routine
    for (int j0 = 0; j0 < j; j0++) { 
      for (int i0 = j0; i0 < i-1; i0++) {
          if (M[i0+1][j0] == 0) {
              i0++; 
          } else if (M[j0][j0] == 0) {
             for (int j1 = 1; j1 < i; j1++) {
                     if (M[j1][j0] != 0) { 
                         mswitch(M,j0,j1); 
                         break;
                     } else { 
                     i0 = i+1; 
                     } 
             } 
          }
          else {
              int lcmi = lcm(M[i0+1][j0],M[j0][j0]);
              mmult (M,j,i0+1,lcmi/M[i0+1][j0]);
              mmult (M,j,j0,lcmi/M[j0][j0]);
              mplus (M,j,j0,i0+1,-1); 
          }
      }
}

    mprint(M,i,j);
}


int main (int argc, char *argv[]) {
    static int** M;
    string sr(argv[3]);
    enterthematrix(M, atoi(argv[1]), atoi(argv[2]),sr);
    return 0;
}

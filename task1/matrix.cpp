#include "header.hpp"
#include <algorithm>

void mswitch (int** a, int f, int s) {
    std::swap(a[f],a[s]);
}

void mmult (int** a, int j, int str, int m) {
    for (int j0 = 0; j0 < j; j0++) a[str][j0] = a[str][j0]*m;
}

void mplus (int** a, int j, int second, int first, int m) {
//  int j = sizeof a[0] / sizeof(int);
    for (int j0 = 0; j0 < j; j0++) a[first][j0] = a[first][j0]+m*a[second][j0];
}
 

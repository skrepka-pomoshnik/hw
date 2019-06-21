#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <string>

static const int Oct = 12, Uni = 0, m2 = 1, M2 = 2, m3 = 3, M3 = 4, p4 = 5, Tr = 6, p5 = 7, m6 = 8, M6 = 9, m7 = 10, M7 = 11; 
static const int C = 0, D = 2, E = 4, F = 5, G = 7, A = 9, B = 11, H = 10; 
static const int _1 = 1, _2 = 2, _3 = 4, _4 = 8, _8 = 16;
static const int up = 1, down = -1, RAND = 2;
inline static const std::string numbertonotes[] = {"c", "cis", "d", "dis", "e", "f", "fis", "g", "gis", "a", "ais", "b"};

enum Motions: int {
    Parallel = 0,
    Oblique = 1,
    Direct = 2,
    Contrary = 3,
};

enum Penalty: int {
    parallels = -7,
    threeparallel = -3,
    directintocons = -3,
    repetition = -8,
    leap = -2,
    compensation = -2,
    dissafterleap = -3,
    uni = -3, //boring
};

enum Bonus: int {
    cadence = 4,
    octaveend = 2,
    contrtoobliq = 2,
};

#endif

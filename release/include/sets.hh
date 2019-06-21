#ifndef SETS_H
#define SETS_H
#include <set>
#include <constants.hh>
inline const std::set<int> Cons = {m3, M3, m6, M6, Oct, p5, Uni,Oct+m3,Oct+M3},
      Diss = {m2,M2,p4,Tr,m7,M7,Oct+m2,Oct+M2},
      AllIntervals = {m3, M3, m6, M6, Oct, p5, Uni,Oct+m3,Oct+M3,m2,M2,p4,Tr,m7,M7,Oct+m2,Oct+M2},
      Perfect = {Oct, p5};

static const std::set<int> Io = {0, 2, 4, 5, 7, 9, 11},
    Do =     {0, 2, 3, 5, 7, 9, 10},
    Ph =   {0, 1, 3, 5, 7, 8, 9},
    Ly =     {0, 2, 4, 6, 7, 9, 11},
    Mi = {0, 2, 4, 5, 7, 9, 10},
    Ae =    {0, 2, 3, 5, 7, 8, 10},
    Lo =    {0, 1, 3, 5, 6, 8, 10 };

extern bool InSet(std::set<int> m, int n);
extern int Dir(int a, int b);
extern int Leap(int a, int b);
#endif


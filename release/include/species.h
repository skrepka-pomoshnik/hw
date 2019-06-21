#pragma once
#ifndef SPECIES_H
#define SPECIES_H

#include <iostream>
#include <cmath>
#include <vector>
#include "tree.hh"
#include "constants.hh"
#include "sets.hh"

typedef tree<std::pair<int,int>>  solutiontree;
typedef std::vector<std::pair<int,int>> phrase;
//std::vector<std::set<int>> Modes = {Io,Do,Ph,Ly,Mi,Ae,Lo};

class Beat { //lower is first
    public:
        Beat (int l,int h) { low = l; high = h; 
            int ainterval = high-low;
            if (ainterval == 0 || ainterval % 12 != 0) {
                interval = ainterval % 12; } else {
                    interval = Oct; }
        }
        Beat (int a1, int a2, int b) { low = a1; low2 = a2; high = b;
            int ainterval = high-low;
            if (ainterval == 0 || ainterval % 12 != 0) {
                interval = ainterval % 12; } else {
                    interval = Oct; }
            ainterval = high-low2;
            if (ainterval == 0 || ainterval % 12 != 0) {
                interval = ainterval % 12; } else {
                    interval = Oct; }
        }
        int high,low,low2,interval,interval1;
};

namespace FirstSpecie {
    void GenerateTree(solutiontree& Stree, phrase Input);
    void AssessPairs(solutiontree& Stree, phrase Input);
    phrase FindBest(solutiontree Ptree, solutiontree::sibling_iterator iter, phrase& Output,phrase Input);
}

namespace SecondSpecie {
    void GenerateTree(solutiontree& Stree, phrase Input);
    void AssessPairs(solutiontree& Stree, phrase Input);
    phrase FindBest(solutiontree Ptree, solutiontree::sibling_iterator iter, phrase& Output,phrase Input);
}

#endif

#include "species.h"

void PrintTreePreorder(const solutiontree& tr, solutiontree::pre_order_iterator it, solutiontree::pre_order_iterator end){
    if(!tr.is_valid(it)) return;
    int rootdepth=tr.depth(it);
    std::cout << std::endl;
    while(it!=end) {
        for(int i=0; i<tr.depth(it)-rootdepth; ++i) 
            std::cout << "  ";
        std::cout << (*it).first << std::endl << std::flush;
        ++it;
    }
    std::cout << std::endl;
}


void PrintTreeBreadth (tree<std::pair<int,int>> Ptree) {
    auto iter = Ptree.begin_breadth_first();
    int d = 0;
    while ( iter != Ptree.end_breadth_first()) {
        if (d < Ptree.depth(iter)) { d++; std::cout << std::endl << d << ":";}
        std::cout << (*iter).first << "(";
        std::cout << (*iter).second << "),";
        iter++;
    }
}

//  std::set<int> WhatMode(phrase Input) {
//  std::set<int> InputMode, OutputMode = Io;
//  for (auto i: Input) InputMode.insert(i.first%12);   
//  int difference = 12;
//  for (auto Mode: Modes) {
//      std::set<int> diff; 
//      std::set_difference(Mode.begin(), Mode.end(), InputMode.begin(), InputMode.end(),
//              std::inserter(diff, diff.end()));
//      if (diff.size() < difference) { 
//          difference = diff.size();
//          OutputMode = Mode; }
//  }
//  auto match = std::find(Modes.begin(),Modes.end(),OutputMode);
//  std::cout << "Mode:" << match - Modes.begin() << std::endl;
//  return OutputMode;
//  }
std::set<int> WhatMode(phrase Input) {
    return Io; 
}


std::set<int> InMode(int Note, std::set<int> Mode, std::set<int> Intervals) {
    Note = Note%12;
    for (auto i: Intervals) {
        int ii = Note -i;
        if (ii < 0) ii+=12;
        if (!InSet(Mode,ii)) Intervals.erase(i);
    }
    return Intervals;
}

int WhatMotion(Beat a, Beat b) { 
    if (a.interval == b.interval) {return Motions(Parallel); } else 
        if (a.high - b.high == 0 || a.low - b.low == 0) {return Motions(Oblique);} else 
            if (Dir(a.low,b.low) == Dir(a.high,b.high)) {return Motions(Direct);} else  {
                return Motions(Contrary);
            }
}

namespace FirstSpecie {
    int CheckPairRules (Beat a, Beat b) {
        int mark = 0;
        if ((a.interval == Uni && b.interval == Uni) || (a.interval == p5 && b.interval == p5) || (a.interval == Oct && b.interval == Oct)) mark += Penalty(parallels); 
        if (WhatMotion(a,b) == Motions(Direct) && InSet(Cons,b.interval)) mark += Penalty(directintocons);
        if(Leap(a.low,b.low) != 0) mark += Penalty(leap);
        if(b.interval == Uni) mark+=Penalty(uni); 
        if(abs(a.low - a.high) > Oct+p5) mark+=Penalty(leap);
        return mark;
    }

    int CheckThreeRules (Beat a, Beat b, Beat c) {
        int mark = 0;
        if (WhatMotion(a,b) == Motions(Parallel) && WhatMotion(b,c) == Motions(Parallel)) mark += Penalty(threeparallel);
        if (a.low == b.low && b.low == c.low) mark += Penalty(repetition);
        if(Leap(a.low,b.low) != 0 && Leap(b.low,c.low) != 0 && Leap(a.low,b.low) == Leap(b.low,c.low)) mark += 2*Penalty(leap); //same dir leaps
        if(WhatMotion(a,b) == Motions(Contrary)) 
            if(WhatMotion(b,c) == Motions(Oblique)) mark+=Bonus(contrtoobliq);
        if(Leap(a.low,b.low) != 0 && Dir(b.low,c.low) == Leap(a.low,b.low)) mark += Penalty(compensation);

        return mark;
    }

    int CheckTheEnd (Beat a, Beat b) {
        int mark = 0;
        if (b.interval == Oct) mark+=Bonus(octaveend);
        if (abs(a.interval) == M3) mark+=Bonus(cadence);
        if ((a.interval == m3 || a.interval == m2) && Dir(a.low,b.low > 0)) mark+=Bonus(cadence);
        return mark;
    }

    void appendSolutions (tree<std::pair<int,int>>& stree, std::set<int> solutions, phrase Input, int i) { //ith note
        if (stree.size() == 1) {
            for(auto const value: solutions) { //append not intervals
                stree.append_child(stree.begin(),std::pair<int,int>(Input[i].first-value,0));
            }
        }
        else { 
            std::vector<tree<std::pair<int,int>>::leaf_iterator> leaves;   
            auto leafiter = stree.begin_leaf();
            while (leafiter != stree.end_leaf()) {
                leaves.push_back(leafiter++);        
            }
            for(auto leaf: leaves) {
                for(auto const value: solutions) {
                    stree.append_child(leaf,std::pair<int,int>(Input[i].first-value,0));
                }
            }
        }
    }

    phrase FindBest(solutiontree Ptree, solutiontree::sibling_iterator iter, phrase& Output,phrase Input) {
        auto max = iter;
        while (iter != iter.end()){ 
            if ((*iter).second > (*max).second) max = iter;
            if (((*iter).second = (*max).second) && rand()%RAND == 0) max = iter;
            iter++;
        }
        int maxtone = (*max).first;
        solutiontree::sibling_iterator it = max;
        if(Ptree.depth(it) != 0)
            Output.push_back(std::make_pair(maxtone,Input[Ptree.depth(it)-1].second));
        if (Ptree.depth(it) < Ptree.max_depth()) {
            FindBest(Ptree, Ptree.begin(it), Output,Input); 
        }
        return Output;
    }

    void GenerateTree(solutiontree& Stree, phrase Input){
        std::set<int> Mode = WhatMode(Input);
        for (unsigned i = 0; i < Input.size(); i++) { 
            std::set<int> Intervals;
            if (i == 0)  { //first
                Intervals = Perfect;
            }  else if (i == Input.size()-1) { //last
                Intervals = Perfect;
                Intervals.insert(Uni);
            }  else if (i == Input.size()-2) {
                Intervals = InMode(Input[i].first,Mode,Cons);
                //  Intervals.insert(m2); //cadence
                Intervals.insert(m3);
            } else {
                Intervals = InMode(Input[i].first,Mode,Cons);
            }
            appendSolutions(Stree,Intervals, Input, i);
        }
    }

    void AssessPairs(solutiontree& Stree, phrase Input) {
        auto iter = Stree.begin_breadth_first();
        int d = 1;
        while ( iter != Stree.end_breadth_first()) {
            if (d < Stree.depth(iter)) d++;
            if (Stree.depth(iter) > 1 && Stree.depth(iter) == d) {
                auto previous = Stree.parent(iter);
                Beat b = Beat((*previous).first,Input[d-2].first);
                Beat c = Beat((*iter).first,Input[d-1].first);
                (*iter).second += CheckPairRules(b,c);

                if (Stree.depth(iter) > 2)  {
                    auto preprevious = Stree.parent(Stree.parent(iter));
                    Beat a = Beat((*preprevious).first,Input[d-3].first);
                    (*iter).second += CheckThreeRules(a,b,c);
                }
                if (Stree.depth(iter) == Stree.max_depth())  {
                    (*iter).second += CheckTheEnd(b,c);
                }
            }
            iter++;
        }
    }
}

namespace SecondSpecie {
    int CheckPairRules (Beat a, Beat b) {
        int mark = 0;
        if ((a.interval == Uni && b.interval == Uni) || (a.interval == p5 && b.interval == p5) || (a.interval == Oct && b.interval == Oct)) mark += Penalty(parallels); 
        if (WhatMotion(a,b) == Motions(Direct) && InSet(Cons,b.interval)) mark += Penalty(directintocons);
        if(Leap(a.low,b.low) != 0) mark += 2*Penalty(leap);
        if(b.interval == Uni) mark+=Penalty(uni); 
        if(abs(a.low-a.high) > Oct+M3) mark+=2*Penalty(leap);
        return mark;
    }

    int CheckThreeRules (Beat a, Beat b, Beat c) {
        int mark = 0;
        if (WhatMotion(a,b) == Motions(Parallel) && WhatMotion(b,c) == Motions(Parallel)) mark += Penalty(threeparallel);
        if (WhatMotion(a,b) == Motions(Oblique) && WhatMotion(b,c) == Motions(Oblique)) mark += Penalty(repetition);
        if(Leap(a.low,b.low) != 0 && Leap(b.low,c.low) != 0 && Leap(a.low,b.low) == Leap(b.low,c.low)) mark += 2*Penalty(leap); 
        if(WhatMotion(a,b) == Motions(Contrary)) 
            if(WhatMotion(b,c) == Motions(Oblique)) mark+=Bonus(contrtoobliq);
        if(Leap(a.low,b.low) != 0 && Dir(b.low,c.low) == Leap(a.low,b.low)) mark += Penalty(compensation);
        return mark;
    }

    int CheckWeakRules (Beat a, Beat b) {
        int mark = 0;
        if (Leap(a.low,b.low) != 0 && InSet(Diss,b.interval)) mark += Penalty(dissafterleap);
        return mark;
    }

    int CheckTheEnd (Beat a, Beat b) {
        int mark = 0;
        if (b.interval == Oct) mark+=Bonus(octaveend);
        if (abs(a.interval) == M3) mark+=Bonus(cadence);
        return mark;
    }

    void appendSolutions (tree<std::pair<int,int>>& stree, std::set<int> solutions,  phrase Input, int i) { //ith note
        if (stree.size() == 1) {
            for(auto const value: solutions) {
                stree.append_child(stree.begin(),std::pair<int,int>(Input[i].first-value,0));
            }
        }
        else { 
            std::vector<tree<std::pair<int,int>>::leaf_iterator> leaves;   
            auto leafiter = stree.begin_leaf();
            while (leafiter != stree.end_leaf()) {
                leaves.push_back(leafiter++);        
            }
            for(auto leaf: leaves) {
                for(auto const value: solutions) {
                    stree.append_child(leaf,std::pair<int,int>(Input[i].first-value,0));
                }
            }
        }
    }

    phrase FindBest(solutiontree Ptree, solutiontree::sibling_iterator iter, phrase& Output,phrase Input) {
        auto max = iter;
        while (iter != iter.end()){ 
            if ((*iter).second > (*max).second) max = iter;
            if (((*iter).second = (*max).second) && rand()%2 == 1) max = iter;
            iter++;
        }
        int maxtone = (*max).first;
        solutiontree::sibling_iterator it = max;
        if(Ptree.depth(it) != 0){
            Output.push_back(std::make_pair(maxtone,Input[(Ptree.depth(it)-1)/2].second*2));
        }
        if (Ptree.depth(it) < Ptree.max_depth()) {
            FindBest(Ptree, Ptree.begin(it), Output,Input); 
        }
        return Output;
    }

    void GenerateTree(solutiontree& Stree, phrase Input){
        std::set<int> Mode = WhatMode(Input);
        for (unsigned i = 0; i < Input.size(); i++) { 
            std::set<int> Intervals1,Intervals2;
            if (i == 0)  { //first or last note
                Intervals1 = Perfect;
                Intervals2 = InMode(Input[i].first,Mode,AllIntervals);
            }  else if (i == Input.size()-1) {
                Intervals1 = Perfect;
                Intervals1.insert(Uni);
                Intervals2 = {};
            } else {
                Intervals1 = InMode(Input[i].first,Mode,Cons); 
                Intervals2 = InMode(Input[i].first,Mode,AllIntervals);
            }
            appendSolutions(Stree,Intervals1, Input, i);
            appendSolutions(Stree,Intervals2, Input, i);
        }
    }

    void AssessPairs(solutiontree& Stree, phrase Input) {
        auto iter = Stree.begin_breadth_first();
        int d = 1; 
        while ( iter != Stree.end_breadth_first()) {
            if (d < Stree.depth(iter)) d++;
            if (Stree.depth(iter) > 1 && Stree.depth(iter) == d) {
                int m = d/2 + 1; //1 1 2 2 3 3
                auto preprevious = Stree.parent(Stree.parent(iter));
                auto previous = Stree.parent(iter);
                Beat b = Beat((*preprevious).first,Input[m].first);
                Beat c = Beat((*iter).first,Input[m-1].first);
                (*iter).second += CheckPairRules(b,c);
                
                if (Stree.depth(iter) % 2 == 0)  {
                (*iter).second += CheckWeakRules(b,c);
                }

                if (Stree.depth(iter) > 3)  {
                    auto ppprevious = Stree.parent(Stree.parent(Stree.parent(Stree.parent(iter)))); //prapraded
                    Beat a = Beat((*ppprevious).first,Input[m-2].first);
                    (*iter).second += CheckThreeRules(a,b,c);
                }
                if (Stree.depth(iter) == Stree.max_depth())  {
                    (*iter).second += CheckTheEnd(b,c);
                }
            }
            iter++;
        }
    }
}

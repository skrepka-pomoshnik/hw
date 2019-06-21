#include "sets.hh"
bool InSet(std::set<int> m, int n) {
    return m.find(n) != m.end();
}

int Dir(int a, int b) {
    int val = b-a;
    return (int(0) < val) - (val < int(0));
}

int Leap(int a, int b) {
    int res = b-a;
    return  (abs(res) > M3)?Dir(a,b):0;
}

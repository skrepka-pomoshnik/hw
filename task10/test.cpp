#include <iostream>
#include <vector>
#include <thread>
#include "aint.h"

//test if atomic
pseudo_atomic_int a;
int b = 0;

int aloop(bool inc, int l) {
    for (int i = 0; i < l; i++) {
        if (inc) { 
            a++;
        } else {
            a--;
        }
    }
    return 0;
}
int bloop(bool inc, int l) {
    for (int i = 0; i < l; i++) {
        if (inc) { 
            b++;
        } else {
            b--;
        }
    }
    return 0;
}



int main() {
    const int NUMTHREADS = 4, BIG=1000000;
    std::vector<std::thread> threads;
    for (int i=1; i<=NUMTHREADS; ++i)
        threads.push_back(std::thread(aloop,true,BIG));
    for (int i=1; i<=NUMTHREADS; ++i)
        threads.push_back(std::thread(aloop,false,BIG));
    for (int i=1; i<=NUMTHREADS; ++i)
        threads.push_back(std::thread(bloop,true,BIG));
    for (int i=1; i<=NUMTHREADS; ++i)
        threads.push_back(std::thread(bloop,false,BIG));
    for (auto& th : threads) th.join();

    std::cout << "should be 0:" << std::endl;
    std::cout << "atomic=" << a << std::endl;
    std::cout << "non atomic=" << b << std::endl;
    return 0;
}


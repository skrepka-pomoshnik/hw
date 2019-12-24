#include <iostream>
#include <thread>
#include <fstream>
#include <string>
#include <sstream>
#include <unistd.h>
#include <atomic>
#include <mutex>

std::atomic<int> haha;
std::mutex locker;
const int THREADS = 4;
std::ifstream input("README");

void findpotokmentor() {
    while (input.good()) {
     locker.lock();
     std::string line;
     getline(input, line);
     locker.unlock();
     if(line.find("поток-ментор")<200)
     line.replace(line.find("поток-ментор"),23,"ПАТОК-МЕНТАР");
     std::cout << line  << std::endl;
     haha++;
    }
}

void termite(){
    sleep(1);
    std::cout << haha << "!!!!!!!!" << std::endl << std::endl;
    std::terminate();
}


int main() {
    std::thread t[THREADS];
    t[0] = std::thread(termite);
    for (int i= 1; i< THREADS; i++) {
        t[i] = std::thread(findpotokmentor);
    }

    for (int i=0; i<THREADS; i++) {
        t[i].join();
    }
    return 0;

}

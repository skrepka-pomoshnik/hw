#include <queue>
#include <iostream>
#include <mutex>
#include <vector>
#include <thread>
#include <condition_variable>

template <class T>
class Queue {
    public: Queue(void): realq(), m(), c(){}

            void in(T t) {
                std::lock_guard<std::mutex> lock(m);
                realq.push(t);
                c.notify_one();
            }

            T out(void) {
                std::unique_lock<std::mutex> lock(m);
                while(realq.empty())
                    c.wait(lock);
                T val = realq.front();
                realq.pop();
                return val;
            }

    private:
            std::queue<T> realq;
            mutable std::mutex m;
            std::condition_variable c;
};


//Test code starts here
Queue<bool> test;

void generator(int t1) {
//    test.in(rand()%10000);
    std::this_thread::sleep_for(std::chrono::milliseconds(t1));
    test.in(false);
}
void incinerator(int t2) {
    std::this_thread::sleep_for(std::chrono::milliseconds(t2));
    if(test.out() == false) std::cout << "-";
}

//void isprime() {
//   int n = test.out(); 
//    std::cout << n;
//    if (n <= 1) 
//        return;
//    for (int i = 2; i < n; i++) 
//        if (n % i == 0) 
//            return; 
//    std::cout << n << " is prime!" << std::endl;
//}

int main (int argc, char* argv[]) {
    const int M = 5, N = 3, L = 1000;
    int t1 = 5,t2 = 5;
    if (argc < 3) return 1;
    t1 = atoi(argv[1]), t2 = atoi(argv[2]);
    srand(time(NULL));

    std::cout << t1 << " "<< t2 << " ";


    for (int j = 0; j < L; j++) {
    std::vector<std::thread> threads(M+N);
    for (int i = 0; i < M; i++) {
        threads[i] = std::thread(generator,t1);
    }
    for (int i = M; i < M+N; i++) {
        threads[i] = std::thread(incinerator,t2);
    }
    for (auto& th : threads) {
        th.join();
    }
    }
    return 0;

}

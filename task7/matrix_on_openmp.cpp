#include <bits/stdc++.h>
#include <chrono> 
#include <omp.h> 
using namespace std; 

const int THREADNUM = 4;
const int size = 100;
int A[size][size]; 
int B[size][size]; 
int C[size][size]; 
int step_i = 0; 

void multi()  { 
    int i,j,k;
    omp_set_num_threads(THREADNUM);
    #pragma omp parallel for private(i,j,k) shared(A,B,C)
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; ++j) {
            for (k = 0; k < size; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
} 

int main()  {
    srand(time(NULL));
    double sum = 0;

    for (int k = 0; k < 100; k++) {
        for (int i = 0; i < size; i++) { 
            for (int j = 0; j < size; j++) { 
                A[i][j] = rand() % RAND_MAX; 
                B[i][j] = rand() % RAND_MAX; 
            } 
        } 

        auto start = std::chrono::high_resolution_clock::now();
        multi();
        auto finish = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = finish - start;
        std::cout << k << "\t" << elapsed.count() << "\t";
        std::cout << 1e-6*size*size*size/elapsed.count() << std::endl;
        sum+=elapsed.count();
    }
    std::cout << sum/100 << std::endl;
    return 0; 
}

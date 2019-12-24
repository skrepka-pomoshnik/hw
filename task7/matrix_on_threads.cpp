#include <bits/stdc++.h> 
#include <chrono> 
using namespace std; 


const int THREADNUM = 4;
const int size = 100;
int A[size][size]; 
int B[size][size]; 
int C[size][size]; 
int step_i = 0; 

void* multi(void* arg)  { 
    int core = step_i++; 

    for (int i = core * size / 4; i < (core + 1) * size / 4; i++)  
        for (int j = 0; j < size; j++)  
            for (int k = 0; k < size; k++)  
                C[i][j] += A[i][k] * B[k][j]; 
    return 0;
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

        step_i = 0;
        pthread_t threads[THREADNUM]; 
        for (int i = 0; i < THREADNUM; i++) { 
            int* p; 
            pthread_create(&threads[i], NULL, multi, (void*)(p)); 
        } 
        for (int i = 0; i < THREADNUM; i++)  
            pthread_join(threads[i], NULL);     

        auto finish = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = finish - start;
    std::cout << k << "\t" << elapsed.count() << "\t";
    std::cout << 1e-6*size*size*size/elapsed.count() << std::endl;
        sum+=elapsed.count();
}
        std::cout << sum/100 << std::endl;
    return 0; 
}

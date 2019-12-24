#include <cstdlib>
#include <iostream>
#include<omp.h>
#include<chrono>

const int NUM_THREADS = 4; 
const int ARR_LEN = 5000; 

void nonstdswap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void printarray(int n, int array[]) {
    int i;
    printf("[%d", array[0]);
    for (i = 1; i < n; i++) 
        printf(", %d", array[i]);
    printf("]\n");
}
int * arraygen(int len){
    int * R = new int [len];
    for(int k = 0; k< len; k++)
        R[k] = (rand()%RAND_MAX)+1;
    return R; 
}

void bubblesort(int arr[], int n) {
    int i, j;
    for (i = 0; i < n-1; i++)      
        for (j = 0; j < n-i-1; j++) 
            if (arr[j] > arr[j+1])
                nonstdswap(&arr[j], &arr[j+1]);
}

void Pbubblesort(int arr[], int n) {
    int k,i,j,temp;
#pragma omp parallel shared(arr, n) private(i, j, temp, k) num_threads(NUM_THREADS)
    for (k = 0; k <= n-2; k++) {
        if (k % 2 == 0){
#pragma omp for
            for (i = 0; i <= (n/2)-1; i++) {
                if (arr[2 * i] > arr[2 * i + 1]) {
                    temp = arr[2 * i];
                    arr[2 * i] = arr[2 * i + 1];
                    arr[2 * i + 1] = temp;
                }
            }
        }
        else {
#pragma omp for
            for (j = 0; j <= (n/2)-2; j++) {
                if (arr[2 * j + 1] > arr[2 * j + 2]) {
                    temp = arr[2 * j + 1];
                    arr[2 * j + 1] = arr[2 * j + 2];
                    arr[2 * j + 2] = temp;
                }
            }
        }
    }
}

int main(){
    srand(time(NULL));
    double sum = 0;
 for (int k = 0; k < 100; k++) {
int* A = arraygen(ARR_LEN);

        auto start = std::chrono::high_resolution_clock::now();
        bubblesort(A,ARR_LEN);
        auto finish = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = finish - start;
       // std::cout << k << "\t" << elapsed.count() << "\t";
        sum+=elapsed.count();
    }
    std::cout << sum/100 << std::endl;
sum = 0;
 for (int k = 0; k < 100; k++) {

int* A = arraygen(ARR_LEN);

        auto start = std::chrono::high_resolution_clock::now();
        Pbubblesort(A,ARR_LEN);
        auto finish = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = finish - start;
      //  std::cout << k << "\t" << elapsed.count() << "\t";
        sum+=elapsed.count();
    }
std::cout << sum/100 << std::endl;


    return 0; 
}

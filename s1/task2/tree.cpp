#include <iostream>

using namespace std;
    const int n = 10; //const
    int t[4*n];

int littlegcd(int a, int b) { 
if (a == 0)  
    return b; 
return littlegcd(b % a, a); 
} 

//int biggcd(int a[], int n) {
//    int res = a[0]; 
//    for (int i = 1; i < n; i++) 
//        res = littlegcd(a[i], res); 
//    return res; 
//}// uneffective gcd

void growatree (int a[], int node, int a1, int a2) {
    if (a1 == a2)
	t[node] = a[a1];
    else {
	int amean = (a1 + a2)/2;
	growatree (a, node*2, a1, amean);
	growatree (a, node*2+1, amean+1, a2);
	t[node] = littlegcd(t[node*2],t[node*2+1]);
    }
}

//update
void leaf (int node, int a1, int a2, int le, int af) {
    if (a1 == a2)
	t[node] = af;
    else {
        int amean = (a1 + a2)/2;
        if (le <= amean)
	leaf (node*2, a1, amean, le, af);
        else
	leaf (node*2+1, amean+1, a2, le, af);
        t[node] = littlegcd(t[node*2],t[node*2+1]); 
    }
}

int main () {
   int A[n] = {10,20,30,40,560,70,80,90,10,110};  // the array
   growatree(A, 1, 0, 9);
    cout << "result:" << t[1] << endl;
///   for (int i=0; i<44; i++) {
//    if ( t[i] != 0) cout << i << ":" << t[i] << endl;
//   }
   leaf(1, 0, 9, 5, 12); // A[5] = 12
   cout << "reresult:" << t[1] << endl;
   return 0;
}

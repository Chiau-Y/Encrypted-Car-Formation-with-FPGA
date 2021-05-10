#include <iostream>
using namespace std;

unsigned long long msg_decrypted =1, i=0, ans=0, a, b, x, y;
unsigned long long e =21, p=23, q=53, n = p*q, r=(p-1)*(q-1); 
unsigned long long A[30],B[30],t;


int main(){
    a = e, b = r;
    A[i] = a;
    B[i] = b;
	while(B[i] != 0){
        i ++;
        A[i] = B[i-1];
        B[i] = A[i-1] % B[i-1];
    }
	unsigned long long p = A[i];
    x = 1,y = 0;
    while(i > 0){
        i --;
        t = x;
        x = y;
        y = t - A[i]/B[i] * y;
    }
    ans = x+r;
    cout << ans << endl;
    return 0;
}
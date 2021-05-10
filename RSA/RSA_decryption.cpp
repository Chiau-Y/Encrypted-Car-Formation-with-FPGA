#include <iostream>
using namespace std;

unsigned long long msg_decrypted =1, i, ans=0;
unsigned long long e =35, p=23, q=53, n = p*q; 
unsigned long long message = 50;

int main(){
    for (i=1; i<=e; i++) {
        msg_decrypted = (msg_decrypted*message)%n; //message^key mod N
    }
    ans = msg_decrypted;
    cout << ans << endl;
    return 0;
}

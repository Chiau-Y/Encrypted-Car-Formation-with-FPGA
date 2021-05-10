#include <iostream>

using namespace std;

void encryption(unsigned long long message, unsigned long long key, unsigned long long N, unsigned long long *ans) {
	unsigned long long sampleVal=1, i;
	for (i=1; i<=key; i++) {
		sampleVal = (sampleVal*message)%N; //message^key mod N
	}
	*ans = sampleVal;
}

int main(){
	unsigned long long ans;
	unsigned long long n = 23*53;
    unsigned long e=35;
    unsigned long d=1979;
    unsigned long msg;

    for( msg = 0; msg <= 1920; msg ++ ){
        encryption(msg,e,n, &ans);
        unsigned long long c = ans;
        printf("Message = %d\t c = %d\n",msg,c);
        if (c > 2047){
            printf("noooooooooo");
        }
    }
    return 0;
}



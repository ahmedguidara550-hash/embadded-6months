#include<stdio.h>

/*Each call uses about 1 KB of stack */
void recurse(unsigned long n){
    volatile char padding[1024];
    padding[0] = (char) n ;
    if (n % 2000 == 0)
    {
        printf("depth = %lu\n",n);
        fflush(stdout);
    }
    recurse(n+1);
    padding[1]=1;
    
}
int main(){
    char big[100000000];
    recurse(1);
    return 0;
}
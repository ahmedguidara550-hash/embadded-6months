#include<stdio.h>
void swap_wrong(int a,int b){
    int tmp = a;
    a=b;
    b=tmp;
}
void swap_right(int *a,int *b){
    int tmp = *a;
    *a = *b ;
    *b =tmp ;
}
int main(){
    int x =1;
    int y =2;
    swap_wrong(x,y);
    printf("after swap_wrong : x=%d y=%d \n",x,y);
    swap_right(&x,&y);
    printf("after swap right : x=%d y=%d",x,y);
    return 0;
}
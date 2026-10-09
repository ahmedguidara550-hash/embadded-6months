#include<stdio.h>
int sum_array(const int *arr,int n){
    int total = 0;
    for(int i=0;i<n;i++){
        total += arr[i];
    }
    return total;
}
/*find the largest number*/
int find_max(const int *arr,int n){
    int max = arr[0];
    for (int i=0;i<n;i++){
        if (arr[i]>max){
            max=arr[i];
        }
    }
    return max;
}
/*fill an array with squares :0,1,4,9,16*/
void fill_with_squares(int *out,int n){
    for (int i=0;i<n;i++){
        out[i] = i*i;
    }
}
int main(){
    int temp[5]={-12,-5,-30,-8,-20};
    printf("sum = %d\n",sum_array(temp,5));
    printf("max = %d\n",find_max(temp,5));
    int *squares = NULL;
    fill_with_squares(squares,5);
    printf("squares[2] = %d\n",squares[2]);
    return 0;
}
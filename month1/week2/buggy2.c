#include <stdio.h>
 
int main(void)
{
    int data[5] = {1, 2, 3, 4, 5};
    int total = 0;
 
    for (int i = 0; i <= 6; i++)
    {
        total += data[i];
    }
 
    printf("total = %d (expected 15)\n", total);
    return 0;
}

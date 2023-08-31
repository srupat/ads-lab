#include<stdio.h>
#include<stdlib.h>
int main()
{
    int n = 5;
    int ** G;
    G = (int **)calloc(n, sizeof(int *));
    // for(int i=0;i<n;i++)
    // {
    //     G[i] = (int*)calloc(n, sizeof(int));
    // }

    printf("%p",G[0][0]);

    return 0;
}
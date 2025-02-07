#include <stdio.h>

int main(){
    int n=3,m=4;
    int a[n][m],i,j;
    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
            a[i][j]=i*j;
    i=2;
    for(j=0;j<m;j++)
        printf("%d",*(*(a+i)+j));
}
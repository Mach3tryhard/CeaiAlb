#include <stdlib.h>
#include <stdio.h>
#include <string.h>
unsigned long long rec(int n)
{
    if(n>0)
        return n*n+rec(n-1);
}

int main(int argc, char *argv[]){
    int sum=atoi(argv[1]);
    printf("%d",rec(sum));
}

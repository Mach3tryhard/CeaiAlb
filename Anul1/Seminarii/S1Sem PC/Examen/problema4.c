#include <stdio.h>
#include <stdlib.h>

int main(){
    const int a=10, *pc=&a;
    const int *const cpc=pc;
    int b,*const cp=&b;
    b=a;
    printf("%d\n",&pc);
    pc=cpc;
    printf("%d",&pc);
    return 0;
}

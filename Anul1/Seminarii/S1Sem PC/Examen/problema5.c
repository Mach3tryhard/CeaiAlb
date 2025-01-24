#include <stdio.h>
#define UNU(x) x+2*x
#define DOI(x) (x)+(2*x)
#define TREI(x) (x+2*x)

int main(){
    int a=3;
    printf("%d\n%d\n%d\n%d\n",2*UNU(a+1),2*DOI(a+1),2*TREI(a+1),a);
    return 0;
}

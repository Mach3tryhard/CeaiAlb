#include <stdio.h>
#include <stdlib.h>

int main(){
    int x=3|(6&2),y=3<<2;
    printf("%d\n%d\n%d",x,y,x&&y);
    return 0;
}

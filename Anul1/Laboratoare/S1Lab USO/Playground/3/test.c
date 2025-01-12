#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main(){
        for(int i=0;i<100;i++){
                int t=isatty(i);
                printf("%d",t);
        }
        return 0;
}

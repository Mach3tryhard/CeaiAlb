#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/wait.h>

int main(){
    int x=0;
    for(fork();!fork();exit(x)){
        printf("Primul Loop!");
        for(!fork();;fork()){
            printf("Al doilea Loop!");
            for(;fork();!fork()){
                printf("Al treilea Loop!");
            }
        }
    }
    printf("%d\n",++x);
    return 0;
}

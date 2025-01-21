#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char **argv){
    int n;
    write(STDOUT_FILENO,"a",sizeof(char));
    n=atoi(argv[1]);
    if(n>=3){
        --n;
        execv(argv[0],argv);
    }
    write(STDOUT_FILENO,"b",sizeof(char));
    return 0;
}

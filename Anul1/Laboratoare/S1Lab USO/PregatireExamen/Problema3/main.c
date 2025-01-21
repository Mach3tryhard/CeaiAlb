#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

int main(){
    int d1,d2;
    char x,y;
    d1=open("f",O_CREAT | O_TRUNC | O_RDWR,S_IRWXU);
    write(d1,"abcde",5*sizeof(char));
    lseek(d1,0,SEEK_SET);

    if(fork()){
        d2=dup(d1);
        sleep(1);
    }
    else{
        d2=open("f",O_RDWR);
    }
    read(d1,&x,sizeof(char));
    read(d2,&y,sizeof(char));

    printf("%c\n%c\n",x,y);
    return 0;
}
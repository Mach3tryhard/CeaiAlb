#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

long simetric(char const *fis){
    FILE* fin=fopen(fis,"r+");
    int fd=open(fis,O_RDWR);
    struct stat fi;
    stat(fis,&fi);
    int sca=fi.st_size-1;

    for(int i=sca;sca>=0;sca--){
        char c;
        lseek(fd,sca,SEEK_SET);
        read(fd,&c,1 * sizeof(char));

        lseek(fd,0,SEEK_END);
        write(fd,&c,1 * sizeof(char));
    }
}

int main(){
    simetric("file.in");
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char fisier1[256],fisier2[256];

    int fold1=-1,fold2=-1;

    if(argc!=3){
        printf("Nu asa se foloseste programul.Ex:%s fisier1 fisier2",argv[0]);
    }

    strcpy(fisier1,argv[1]);
    strcpy(fisier2,argv[2]);

    struct stat fs1,fs2;

    if (stat(fisier1, &fs1) == -1) {
        perror("No folder or file with that name");
    }
    else{
        if (S_ISREG(fs1.st_mode))
        fold1=0;
        if (S_ISDIR(fs1.st_mode))
            fold1=1;
    }

    if (stat(fisier2, &fs2) == -1) {
        perror("No folder or file with that name");
    }
    else{
        if (S_ISREG(fs2.st_mode))
            fold2=0;
        if (S_ISDIR(fs2.st_mode))
            fold2=1;
    }

    printf("Debug:%d %d",fold1,fold2);

    if(fold1==0 && fold2==-1){
        rename(fisier1, fisier2);
    }
    if(fold1==0 && fold2==0){
        int fd1=open(fisier1,O_RDWR);
        char c[1];
        int fd2=open(fisier2,O_RDWR | O_TRUNC);

        while(read( fd1,c,1 )>0){
            write(fd2, c, 1);
        }
    }
    if(fold1==0 && fold2==1){
        char fullpath[512]="\0";
        strcat(fullpath,fisier2);
        if(fisier2[strlen(fisier2)-1]!='/'){
            strcat(fullpath,"/");
        }
        strcat(fullpath,fisier1);
        int caca=link( fisier1,fullpath );
        int caca1=unlink(fisier1);
    }
    return 0;
}

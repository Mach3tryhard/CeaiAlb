#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc,char *argv[]){
    if(argc!=3){
        printf("Nu asa se foloseste programul:%s pathname1 pathname2",argv[0]);
        return -1;
    }

    int fd1=open(argv[1],O_RDWR);
    int fd2=open(argv[2],O_RDWR);

    FILE *fin1=fopen(argv[1],"r");
    FILE *fin2=fopen(argv[2],"r");

    struct stat fi1,fi2;
    stat(argv[1],&fi1);
    stat(argv[2],&fi2);

    char c1,c2;
    int dif=0;
    int n=fi1.st_size;int m=fi2.st_size;

    int ver1=0,ver2=0;
    while( ver1<n && ver2<m && dif==0 ){
        read(fd1,&c1,1);
        read(fd2,&c2,1);
        if(c1>c2)dif=1;
        if(c1<c2)dif=-1;
        ver1+=1;ver2+=1;
    }
    if(dif==0){
        if(ver1==n && ver2!=m)dif=-1;
        if(ver2==m && ver1!=n)dif=1;
        if(ver2==m && ver1==n)dif=0;
    }
    printf("%d",dif);
    return 0;
}
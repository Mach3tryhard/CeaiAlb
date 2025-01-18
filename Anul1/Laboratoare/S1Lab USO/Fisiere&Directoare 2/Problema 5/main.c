#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc,char *argv[]){
    if(argc!=3){
        printf("Nu asa se foloseste programul:%s pathname1 pathname2",argv[0]);
        return -1;
    }

    FILE *fin1=fopen(argv[1],"r");
    FILE *fin2=fopen(argv[2],"r");
    int test=1;
    char v1[1024]="\0",v2[1024]="\0";
    char c;
    while ((c = fgetc(fin1)) != EOF) {
        strcat(v1,&c);
    }

    while ((c = fgetc(fin2)) != EOF) {
        strcat(v2,&c);
    }

    int count = 0;
    const char *temp = v2;
    while ((temp = strstr(temp, v1)) != NULL) {
        count++;
        temp++;
    }
    printf("%d",count);
    return 0;
}
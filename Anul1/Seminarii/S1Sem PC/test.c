#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int main(){
    FILE*fout=fopen("file.b","wb");
    char *caca="caca";
    fwrite(caca,sizeof(char),4,fout);
    return 0;    
}
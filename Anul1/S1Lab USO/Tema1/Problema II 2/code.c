#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int eof(int d){

}

int main(){

    FILE* fin = fopen("text.in","r");
    FILE* fout = fopen("text.out","w");

    

    fclose(fin);
    fclose(fout);
    return 0;
}
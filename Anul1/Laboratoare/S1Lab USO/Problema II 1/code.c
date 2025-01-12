#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Comun(char *a,char *b){
    if(strstr(b,a)!=NULL){
        return 1;
    }
    else{
        return 0;
    }
}

int main(int argc, char *argv[]){
    if(argc!=4){
        fprintf(stderr,"Utilizare: %s -f freg ftext\n",argv[0]);
        return 1;
    }
    if(strcmp(argv[1],"-f")!=0){
        fprintf(stderr,"Flagul %s nu exista sau ordinea argumentelor e gresita!\n",argv[1]);
        return 1;
    }

    FILE* fin = fopen(argv[2],"r");
    if(fin==NULL){
        perror(argv[2]);
        return 1;
    }
    FILE* fout = fopen(argv[3],"r");
    if(fout==NULL){
        perror(argv[3]);
        return 1;
    }

    char pattern[256];
    char line[256];
    while(fgets(line,sizeof(line),fout)){
        
        fseek(fin, 0, SEEK_SET);
        while(fgets(pattern, sizeof(pattern), fin)){
            if(Comun(pattern,line)==1){
                printf("%s",line);
                break;
            }
        }
    }

    fclose(fin);
    fclose(fout);
    return 0;
}
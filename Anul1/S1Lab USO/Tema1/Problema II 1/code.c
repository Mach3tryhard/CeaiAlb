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
    if(strcmp(argv[1],"-f")!=0){
        printf("Flagul %s nu exista sau ordinea argumentelor e gresita!\n",argv[1]);
        return 0;
    }
    
    if(argc!=4){
        printf("Numarul de argumente nu este corect!\n");
        return 0;
    }

    FILE* fin = fopen(argv[2],"r");
    FILE* fout = fopen(argv[3],"r");
    
    if(fin==NULL){
        printf("Primul fisier nu exista!\n");
        return 0;
    }
    if(fout==NULL){
        printf("Al doilea fisier nu exista!\n");
        return 0;
    }

    char pattern[256],line[256];

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
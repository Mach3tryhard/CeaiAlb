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
    int ps=2,ls=2;
    char pattern[256];
    char *line=malloc(sizeof(char)* ls);

    char c1,c2;

    c2 = fgetc(fout);
    line[0]=c2;
    line[1]='\0';
    while((c2 = fgetc(fout)) != EOF && c2 != '\n'){
        fseek(fin, 0, SEEK_SET);

        ls++;
        char *line = realloc(line, ls * sizeof(char));
        line[ls-2]=c2;
        line[ls-1]='\0';

        while(fgets(pattern, sizeof(pattern), fin)){
            size_t len = strlen(pattern);
            if (len > 0 && pattern[len - 1] == '\n') {
                pattern[len - 1] = '\0';
            }

            if(Comun(pattern,line)==1){
                printf("%s",line);
                break;
            }
        }
    }
    free(line);
    fclose(fin);
    fclose(fout);
    return 0;
}

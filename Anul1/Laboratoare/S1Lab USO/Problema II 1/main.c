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
    char *pattern=malloc(sizeof(char)* ps);
    if(pattern==NULL){
        fprintf(stderr,"Alocarea de memorie nu a mers");
        return 1;
    }
    char *line=malloc(sizeof(char)* ls);
    if(line==NULL){
        fprintf(stderr,"Alocarea de memorie nu a mers");
        return 1;
    }

    int intc1,intc2;
    char c1,c2;

    intc2 = fgetc(fout);
    c2=(char)intc2;
    line[0]=c2;
    line[1]='\0';
    while((intc2 = fgetc(fout)) != EOF){
        fseek(fin, 0, SEEK_SET);

        c2=(char)intc2;
        ls++;
        line = realloc(line, ls * sizeof(char));
        if(line==NULL){
            fprintf(stderr,"Alocarea de memorie nu a mers");
            return 1;
        }
        line[ls-2]=c2;
        line[ls-1]='\0';

        if(c2=='\n' || intc2==-1){
            intc1=fgetc(fin);
            c1 = (char)intc1;
            pattern[0]=c1;
            pattern[1]='\0';

            while((intc1 = fgetc(fin)) != EOF){
                c1=(char)intc1;

                ps++;
                pattern = realloc(pattern, ps * sizeof(char));
                if(pattern==NULL){
                    fprintf(stderr,"Alocarea de memorie nu a mers");
                    return 1;
                }
                pattern[ps-2]=c1;
                pattern[ps-1]='\0';

                if(c1=='\n'  || intc1==-1){
                    size_t len = strlen(pattern);
                    if (len > 0 && pattern[len - 1] == '\n') {
                        pattern[len - 1] = '\0';
                    }
                    //printf("%s %s\n",line,pattern);
                    if(Comun(pattern,line)==1){
                        printf("%s",line);
                        break;
                    }
                    ps=1;
                    pattern= realloc(pattern, ps * sizeof(char));
                    if(pattern==NULL){
                        fprintf(stderr,"Alocarea de memorie nu a mers");
                        return 1;
                    }
                    pattern[0]='\0';
                }
            }
            ls=1;
            line= realloc(line, ls * sizeof(char));
            if(line==NULL){
                fprintf(stderr,"Alocarea de memorie nu a mers");
                return 1;
            }
            line[0]='\0';
        }
    }
    free(line);
    free(pattern);
    fclose(fin);
    fclose(fout);
    return 0;
}
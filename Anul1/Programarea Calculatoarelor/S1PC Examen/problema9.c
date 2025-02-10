#include <stdio.h>
#include <string.h>

int main(){
    FILE* fin=fopen("text.txt","r+");
    FILE* fout=fopen("linie.txt","w+");
    char c,uc='0';
    char  line[501],rez[501];
    int maxcuv=0,curcuv=0,i=0,siz=0;
    while((c=fgetc(fin))!=EOF)
    {
        line[i]=c;
        i++;
        if(c=='\n'){
            if( (uc>='a' && uc<='z') || (uc>='A' && uc<='Z')){
                curcuv++;
            }
            if(curcuv>maxcuv){
                maxcuv=curcuv;
                strcpy(rez,line);
                siz=i;
            }
            i=0;
            curcuv=0;
        }
        if( (c==' ' || c=='.' || c==',') && ((uc>='a' && uc<='z') || (uc>='A' && uc<='Z'))){
            curcuv++;
        }
        uc=c;
    }
    if(curcuv>maxcuv){
        strcpy(rez,line);
        siz=i;
    }

    for(int j=0;j<siz;j++){
        fprintf(fout,"%c",rez[j]);
    }
    close(fin);
    close(fout);
    return 0;
}

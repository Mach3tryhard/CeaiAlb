#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct produs{
    char denumire[15],categorie[15];
    float pret;
}v[105];

int main(){
    FILE* fin=fopen("a.in","r+");
    FILE* fout=fopen("caca.bin","wb");
    int n,max=0;
    fscanf(fin,"%d",&n);
    for(int i=0;i<n;i++){
        fscanf(fin,"%s",v[i].denumire);
        fscanf(fin,"%s",v[i].categorie);
        fscanf(fin,"%f",&v[i].pret);
        if(v[i].pret>max){
            max=v[i].pret;
        }
    }
    //A
    for(int i=n-1;i>=0;i--){
        if(strcmp(v[i].categorie,"papetarie")==0){
            printf("%s\n",v[i].denumire);
            printf("%s\n",v[i].categorie);
            printf("%f\n",v[i].pret);
        }
    }
    //B
    for(int i=n-1;i>=0;i--){
        if(v[i].pret==max){
            fwrite(&v, sizeof(struct produs), 1, fout);
        }
    }
    return 0;
}

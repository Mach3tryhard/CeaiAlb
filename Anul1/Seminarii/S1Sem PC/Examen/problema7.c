#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int n;
int *v;

int cmp(const void* a, const void* b)
{
    int arg1=*(const int*)a;
    int arg2=*(const int*)b;
    if(arg1<arg2) return -1;
    if(arg1>arg2) return 1;
    return 0;
}

void Citire(FILE* fin){
    fscanf(fin,"%d",&n);
    v=malloc(n*sizeof(int));
    for(int i=0;i<n;i++){
        fscanf(fin,"%d",&v[i]);
    }
    for(int i=0;i<n;i++){
        printf("%d ",v[i]);
    }
    close(fin);
}

long long Suma(int p1,int p2){
    int kon=0;
    for(int i=p1+1;i<=p2;i++){
        if(v[i]<0)
            kon+=v[i];
    }
    return kon;
}

int main(){
    FILE* fin=fopen("a.in","r+");
    Citire(fin);
    int a,b;
    fscanf(fin,"%d%d",&a,&b);
    int sum=Suma(a,b);
    printf("\n%d",sum);
    qsort(v,n,sizeof(int),cmp);
    printf("\n");
    for(int i=0;i<n;i++){
        printf("%d ",v[i]);
    }
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char v[10000];
    v[0]='0';v[1000]='8';
    v[1]='1';v[1001]='9';
    v[10]='2';v[1010]='A';
    v[11]='3';v[1011]='B';
    v[100]='4';v[1100]='C';
    v[101]='5';v[1101]='D';
    v[110]='6';v[1110]='E';
    v[111]='7';v[1111]='F';

    char nr[1005];
    scanf("%s",nr);
    int val=0,k;
    if(strlen(nr)%4!=0){
        k+=4-strlen(nr)%4;
    }
    for(int i=0;i<strlen(nr);i++){
        val=val*10+nr[i]-'0';
        if(k==4){
            printf("%c",v[val]);
            k=0;
            val=0;
        }
        k++;
    }
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>

int main(){
    char a[1005]="abc",b[1005]="abb";
    printf("%d",isdigit('9'));
    return 0;
}
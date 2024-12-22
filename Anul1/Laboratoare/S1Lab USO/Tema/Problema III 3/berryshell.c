#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

void sigintHandler(int sig_num) { 
    printf("\n>");
    fflush(stdout);
    signal(SIGINT, sigintHandler); 
}
void sighandler(int sig_num) {
    printf("\n>");
    fflush(stdout);
    signal(SIGTSTP, sighandler); 
} 

int main(){
    char* PATH=getenv("PATH");
    char str[1000]="\0";

    signal(SIGINT, sigintHandler); 
    signal(SIGTSTP, sighandler); 
    printf(">");

    while(1){
        fflush(stdin);
        fgets(str,sizeof(str),stdin);
        if(strcmp(str,"exit\n")==0){
            break;
        }
        int found=0;

        if(found==0){
            printf("Comanda nu exista\n");
        }
        printf(">");
    }
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int vf[10]={0};
char str[20]="";

int n;

int main(int argc,char* argv[])
{
    ///CREATE PIPE
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe o murit");
        exit(EXIT_FAILURE);
    }

    if(argc==3)///CLOSE CHILD READ PIPE
        //close(pipefd[0]);
    if(argc==2)
        //close(pipefd[1]);

    if (argc> 3) {
        fprintf(stderr, "Utilizare: %s <n> [prefix]\n", argv[0]);
        return 1;
    }
    ///CONVERTIRE argumente la int
    if(argc>=2){
        str[0]=0;
        n=argv[1][0]-'0';
    }
    if(argc==3){
        strcpy(str, argv[2]);
        int m=strlen(argv[2]);
        for(int i=0;i<m;i++){
            vf[argv[2][i]-'0']=1;
        }
    }
    int m=strlen(str);

    ///CREARE FORK CU O CIFRA IN PLUS IN PERMUTARE
    for(int i=1;i<=n;i++){
        if(vf[i]==0  && m<n){
            pid_t pid=fork();
            if (pid==-1) {
                perror("fork o murit");
                return 1;
            }
            if (pid==0){
                char tmp[2];
                tmp[0]='0' + i;
                tmp[1]='\0';
                char str_copy[20];
                strcpy(str_copy, str);
                strcat(str_copy, tmp); 

                char *program = argv[0];
                char *args[4];
                args[0] = argv[0];
                args[1] = argv[1];
                args[2] = str_copy;
                args[3] = NULL;

                char *env[] = {NULL};
                execve(program, args, env);
                close(pipefd[1]);

                perror("execve o murit");
                return 1;
            }
            /// ASTEAPTA COPIL DACA TREBUIE
            //waitpid(pid, NULL, 0);
        }
    }
    ///COPILUL SCRIE IN PIPE DACA ARE PERMUTARE
    if(n==m){
        if (write(pipefd[1], argv[2], strlen(argv[2])) == -1) {
            perror("write pipe error");
            exit(EXIT_FAILURE);
        }
        write(pipefd[1], "\n", 1);
        //printf("%s\n",argv[2]);
    }
    close(pipefd[1]);

    //if(argc==2){
        char buffer[1024];
        ssize_t bytesRead = read(pipefd[0], buffer, sizeof(buffer) - 1);
        while(bytesRead>0){
            buffer[bytesRead] = '\0';
            printf("%s\n",buffer);
        }
    //}

    close(pipefd[0]);

    while (wait(NULL) > 0)
        ;
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int vf[10]={0};

int main(int argc,char* argv[])
{
    if (argc <2 || argc> 3) {
        fprintf(stderr, "Utilizare: %s <n> [prefix]\n", argv[0]);
        return 1;
    }
    ///CONVERTIRE
    char str[20]="";
    str[0]=0;
    int n=argv[1][0]-'0';
    if(argc==3){
        strcpy(str, argv[2]);
        int m=strlen(argv[2]);
        for(int i=0;i<m;i++){
            vf[argv[2][i]-'0']=1;
        }
    }

    int m=strlen(str);

    for(int i=1;i<=n;i++){
        if(vf[i]==0  && m<n){
            pid_t pid=fork();
            if (pid==-1) {
                perror("fork failed");
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

                perror("execve o murit");
                return 1;
            }
            //waitpid(pid, NULL, 0);
        }
    }
    if(n==m)
        printf("%s\n",argv[2]);
    return 0;
}

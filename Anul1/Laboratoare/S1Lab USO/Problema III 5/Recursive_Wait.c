#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int n=0, x[10]={0},k=0;

int main(int argc,char* argv[])
{
    ///CONVERTIRE
    int l=strlen(argv[1]);
    for(int i=0;i<l;i++){
        if(argv[1][i]<'0' || argv[1][i]>'9'){
            fprintf(stderr,"%s nu este numar natural",argv[1]);
            return 1;
        }
        n=n*10+(argv[1][i]-'0');
    }
    if(argc!=3 && argc!=3+n){
        fprintf(stderr,"Utilizare: %s n k\n",argv[0]);
        return 1;
    }
    l=strlen(argv[2]);
    for(int i=0;i<l;i++){
        k=k*10+(argv[2][i]-'0');
    }
    ///Luam vectorul parintelui din argumente
    if(argc>3){
        for(int i=3;i<3+n;i++){
            x[i-3]=atoi(argv[i]);
        }
    }
    /// BACKTRACKINGURL
    for(int i=1;i<=n;i++)
    {
        int verificare=1;
        x[k]=i;
        for(int i=1;i<k;++i)
        {
            if(x[i]==x[k])
            {
                verificare=0;
            }
        }
        if(verificare==1)
        {
            if(k==n)
            {
                for(int i=1;i<=n;i++)
                {
                    printf("%d ",x[i]);
                }
                printf("\n");
            }
            else
            {
                pid_t pid=fork();
                if (pid==-1) {
                    perror("fork failed");
                    return 1;
                }
                if (pid==0){
                    char *program = argv[0];
                    char *args[3 + n + 1];
                    char buffer[10];

                    args[0] = argv[0];
                    args[1] = argv[1];
                    sprintf(buffer, "%d", k + 1);
                    args[2] = strdup(buffer);

                    for (int j = 3; j < 3 + n; j++) {
                        sprintf(buffer, "%d", x[j - 3]);
                        args[j] = strdup(buffer);
                    }
                    args[3 + n] = NULL;

                    char *env[] = {NULL};
                    execve(program, args, env);

                    perror("execve failed");
                    exit(1);
                }
                waitpid(pid, NULL, 0);
            }
        }
    }
    return 0;
}

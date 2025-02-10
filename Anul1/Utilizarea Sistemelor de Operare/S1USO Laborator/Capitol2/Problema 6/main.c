#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc,char *argv[]){
    FILE* fin=fopen(argv[1],"r");

    int pipefd[2];
    pipe(pipefd);

    char v[1024];
    char c;
    int it=0;
    while(c=fgetc(fin)!=EOF){
        v[it]=c;
        it+=1;
    }
    fclose(fin);

    int a=atoi(argv[2]);
    int b=atoi(argv[3]);
    if(a!=b){
        for(int i=0;i<=1;i++){
        pid_t pid = fork();
            if (pid == -1) {
                perror("fork a murit");
                return -1;
            }
            if (pid == 0) {
                close(pipefd[0]);

                char *program = argv[0];
                char *args[4];
                args[0] = argv[0];
                args[1] = argv[1];
                if(i==0){
                    sprintf(args[2], "%d", a);
                    sprintf(args[3], "%d", (a+b)/2);
                }
                if(i==1){
                    sprintf(args[2], "%d", (a+b)/2+1);
                    sprintf(args[3], "%d", b);
                }
                args[4]=NULL;
                printf("%s %s program cu acest ab \n",args[2],args[3]);
                execve(program, args, NULL); 

                perror("execve a murit");
                exit(EXIT_FAILURE);
            }
        }
    }
    

    if(a==b){
        char str[b-a+1];
        for(int i=a;i<=b;i++){
            str[i-a]=v[i];
        }
        write(pipefd[1],str,strlen(str));
    }
    else{
        char buffer[1024];
		ssize_t bytesRead;
        /*while((bytesRead=read(pipefd[0],buffer,sizeof(buffer)-1))>0){
			buffer[bytesRead]='\0';
			printf("%s",buffer);
		}*/
    }

    return 0;
}
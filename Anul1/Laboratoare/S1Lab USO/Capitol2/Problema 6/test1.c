#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc,char *argv[]){
    FILE* fin=fopen(argv[1],"r");

    int pipefd[2];
    pipe(pipefd);

    char v[1024];
    char c;
    int it=0;
    while((c=fgetc(fin))!=EOF){
        v[it]=c;
        it+=1;
    }
    fclose(fin);

    int a=atoi(argv[2]);
    int b=atoi(argv[3]);
    if(a!=b){
        int pid[2];
        for(int i=0;i<=1;i++){
            pid[i] = fork();
            if (pid[i] == 0) {
                close(pipefd[0]); // Child only writes, so close the read end

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
                args[4] = NULL;
                execve(program, args, NULL);
                exit(EXIT_FAILURE); 
            }
        }

        for(int i=0;i<=1;i++)
            waitpid(pid[i],NULL,0);

        close(pipefd[1]); // Parent only reads after this, close the write end

        char left[512], right[512];
        ssize_t leftBytes = read(pipefd[0], left, sizeof(left) - 1);
        ssize_t rightBytes = read(pipefd[0], right, sizeof(right) - 1);
        left[leftBytes] = '\0';
        right[rightBytes] = '\0';

        char result[1024];
        int li = 0, ri = 0, ri_out = 0;
        while(li < leftBytes && ri < rightBytes) {
            if(left[li] <= right[ri]) result[ri_out++] = left[li++];
            else result[ri_out++] = right[ri++];
        }
        while(li < leftBytes) result[ri_out++] = left[li++];
        while(ri < rightBytes) result[ri_out++] = right[ri++];
        result[ri_out] = '\0';

        printf("%s\n", result); // Print the final sorted result
        close(pipefd[0]); // Close the read end
    }
    else{
        close(pipefd[0]); // Child only writes, close the read end
        char str[2] = {v[a], '\0'};
        write(pipefd[1], str, 1);
        close(pipefd[1]); // Close the write end after writing
    }
    return 0;
}

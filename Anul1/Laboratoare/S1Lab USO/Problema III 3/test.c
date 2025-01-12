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
    char* PATH = getenv("PATH");
    char str[1000] = "\0";
    signal(SIGINT, sigintHandler); 
    signal(SIGTSTP, sighandler); 
    printf(">");

    while (1) {
        fgets(str, sizeof(str), stdin);
        if (strcmp(str, "exit\n") == 0) {
            break;
        }

        str[strcspn(str, "\n")] = 0; // Remove newline character from input

        char *token = strtok(PATH, ":");
        int found = 0;

        while (token != NULL) {
            char cmd[1000];
            snprintf(cmd, sizeof(cmd), "%s/%s", token, str);
            if (access(cmd, X_OK) == 0) {
                pid_t pid = fork();
                if (pid == 0) {
                    execlp(cmd, str, (char *)NULL);
                    exit(0); // Exit after executing the command
                } else {
                    wait(NULL); // Wait for the child process to finish
                    found = 1;
                    break;
                }
            }
            token = strtok(NULL, ":");
        }

        if (!found) {
            printf("Command not found\n");
        }

        printf(">");
    }
    return 0; 
}

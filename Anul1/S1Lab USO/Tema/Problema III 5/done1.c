#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int vf[10] = {0};
char str[20] = "";
int n;

int main(int argc, char* argv[]){

    ///PARCURGERE AL ARGUMENTELOR
	int pipefd[2];
	if (pipe(pipefd) == -1) {
		perror("pipe nu a mers");
		return 1;
	}
	if (argc == 1) {
		fprintf(stderr, "Usage: %s <n>\n", argv[0]);
		return 1;
	}

	if (argc >= 2) {
		str[0] = 0;
		n = argv[1][0] - '0';
	}
	if (argc >=3) {
		strcpy(str, argv[2]);
		int m = strlen(argv[2]);
		for (int i = 0; i < m; i++) {
			vf[argv[2][i] - '0'] = 1;
		}
	}
    if (argc == 4) {
        int write_fd = atoi(argv[3]); 
        pipefd[0] = -1;               
        pipefd[1] = write_fd;         
    }

    ///BACKTRACKING

	int m = strlen(str);

	for (int i = 1; i <= n; i++) {
		if (vf[i] == 0 && m < n) {
            ///CREAZA COPIL
			pid_t pid = fork();
			if (pid == -1) {
				perror("fork nu a mers");
				return 1;
			}
			if (pid == 0) {
				close(pipefd[0]);

				char tmp[2];
				tmp[0] = '0' + i;
				tmp[1] = '\0';
				char str_copy[20];
				strcpy(str_copy, str);
				strcat(str_copy, tmp);

				if (strlen(str_copy) == n) {
					strcat(str_copy, "\n");
					write(pipefd[1], str_copy, strlen(str_copy));
					//write(pipefd[1], "\n", 1);
				}
                ///DA CA ARGUMENT PIPEUL PARINTELUI
				char pipe_write_fd[10];
				snprintf(pipe_write_fd, sizeof(pipe_write_fd), "%d", pipefd[1]);

				char *args[5];
				args[0] = argv[0]; /// PROGRAMUL
				args[1] = argv[1]; /// NUMARUL n
				args[2] = str_copy; ///PERMUTAREA NOUA
				args[3] = pipe_write_fd; /// PIPEUL ORIGINAL
				args[4] = NULL;

				execve(argv[0], args, NULL); 
				perror("execve nu a mers");
				return 1;
			}
		}
	}

	close(pipefd[1]);

    ///PARINTELE CITESTE DIN PIPE (DOAR EL ARE 2 ARGUMENTE)

	if (argc == 2) {
		char buffer[1024];
		int  bytesRead;
		while ((bytesRead = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0) {
			buffer[bytesRead] = '\0';
			printf("%s", buffer);
		}
	}

	close(pipefd[0]);
	return 0;
}

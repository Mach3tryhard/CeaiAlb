#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int vf[10] = {0};
char str[20] = "";
int n;

int main(int argc, char* argv[]) {
	int pipefd[2];
	if (pipe(pipefd) == -1) {
		perror("pipe a murit");
		exit(EXIT_FAILURE);
	}
	if (argc > 3) {
		fprintf(stderr, "Utilizare: %s <n>\n", argv[0]);
		return 1;
	}

	if (argc >= 2) {
		str[0] = 0;
		n = argv[1][0] - '0';
	}
	if (argc == 3) {
		strcpy(str, argv[2]);
		int m = strlen(argv[2]);
		for (int i = 0; i < m; i++) {
			vf[argv[2][i] - '0'] = 1;
		}
	}
	int m = strlen(str);

	for (int i = 1; i <= n; i++) {
		if (vf[i] == 0 && m < n) {
			pid_t pid = fork();
			if (pid == -1) {
				perror("fork a murit");
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
					write(pipefd[1], str_copy, strlen(str_copy));
					write(pipefd[1], "\n", 1);
				}

                char *program = argv[0];
                char *args[4];
                args[0] = argv[0];
                args[1] = argv[1];
                args[2] = str_copy;
                args[3] = NULL;

                execve(program, args, NULL); 

				perror("execve a murit");
				exit(EXIT_FAILURE);
			}
		}
	}
	close(pipefd[1]);
	if(argc==2){
		char buffer[1024];
		ssize_t bytesRead;
		while((bytesRead=read(pipefd[0],buffer,sizeof(buffer)-1))>0){
			buffer[bytesRead]='\0';
			printf("%s",buffer);
		}
	}
	close(pipefd[0]);
	while(wait(NULL)>0);
	/*close(pipefd[1]);

	char buffer[1024];
	ssize_t bytesRead;
	while ((bytesRead = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0) {
		buffer[bytesRead] = '\0';
		printf("%s", buffer);
	}
	close(pipefd[0]);*/
	return 0;
}

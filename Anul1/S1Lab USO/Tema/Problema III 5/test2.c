#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_N 10

int vf[MAX_N + 1] = {0};
char str[20] = "";
int n;
int pipefd[2];

void generate_permutations(int depth) {
    if (depth == n) {
        // Dacă am completat o permutare, o scriem în tub
        if (write(pipefd[1], str, strlen(str)) == -1) {
            perror("write failed");
            exit(EXIT_FAILURE);
        }
        if (write(pipefd[1], "\n", 1) == -1) {
            perror("write failed");
            exit(EXIT_FAILURE);
        }
        return;
    }

    for (int i = 1; i <= n; i++) {
        if (!vf[i]) {
            // Marcare element utilizat
            vf[i] = 1;
            char tmp[2];
            tmp[0] = '0' + i;
            tmp[1] = '\0';
            strcat(str, tmp);

            pid_t pid = fork();
            if (pid == -1) {
                perror("fork failed");
                exit(EXIT_FAILURE);
            }

            if (pid == 0) { // Proces copil
                generate_permutations(depth + 1); // Apel recursiv în procesul copil
                exit(EXIT_SUCCESS);
            }

            // Procesul părinte continuă să exploreze alte opțiuni
            //vf[i] = 0;
            //str[strlen(str) - 1] = '\0';
        }
    }
    while (wait(NULL) > 0)
        ;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Utilizare: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    n = atoi(argv[1]);
    if (n <= 0 || n > MAX_N) {
        fprintf(stderr, "n trebuie să fie între 1 și %d.\n", MAX_N);
        return EXIT_FAILURE;
    }

    // Crearea tubului anonim
    if (pipe(pipefd) == -1) {
        perror("pipe failed");
        return EXIT_FAILURE;
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork failed");
        return EXIT_FAILURE;
    }

    if (pid == 0) { // Proces copil: generează permutări
        close(pipefd[0]); 
        generate_permutations(0);
        close(pipefd[1]); 
        exit(EXIT_SUCCESS);
    }
    // Proces părinte: citește permutările din tub
    close(pipefd[1]); 
    char buffer[1024];
    ssize_t bytes_read;
    while ((bytes_read = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytes_read] = '\0';
        printf("%s", buffer);
    }
    close(pipefd[0]);

    while (wait(NULL) > 0)
        ;
    return EXIT_SUCCESS;
}

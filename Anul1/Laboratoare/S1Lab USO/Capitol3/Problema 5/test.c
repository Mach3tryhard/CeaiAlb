#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_N 10

int n;
int pipefd[2];

void generate_permutations(int depth, int *used, char *current) {
    // Dacă am completat o permutare, scriem în tub
    if (depth == n) {
        if (write(pipefd[1], current, strlen(current)) == -1) {
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
        if (!used[i]) {
            // Marcare element utilizat
            used[i] = 1;
            char next_current[MAX_N * 2];
            snprintf(next_current, sizeof(next_current), "%s%d", current, i);

            pid_t pid = fork();
            if (pid == -1) {
                perror("fork failed");
                exit(EXIT_FAILURE);
            }

            if (pid == 0) { // Proces copil
                generate_permutations(depth + 1, used, next_current);
                exit(EXIT_SUCCESS);
            }
            // Procesul părinte continuă să exploreze alte opțiuni
            used[i] = 0; // Deblocăm elementul pentru alte permutări
        }
    }

    // Așteptăm toți copiii să termine
    while (wait(NULL) > 0)
        ;
}

int main() {
    // Citirea valorii lui n
    printf("Enter n: ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX_N) {
        fprintf(stderr, "Invalid input. n must be between 1 and %d.\n", MAX_N);
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
        close(pipefd[0]); // Închidem capătul de citire al tubului

        int used[MAX_N + 1] = {0};
        char current[MAX_N * 2] = "";
        generate_permutations(0, used, current);

        close(pipefd[1]); // Închidem capătul de scriere al tubului
        exit(EXIT_SUCCESS);
    }

    // Proces părinte: citește permutările din tub
    close(pipefd[1]); // Închidem capătul de scriere al tubului

    char buffer[1024];
    ssize_t bytes_read;
    while ((bytes_read = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytes_read] = '\0'; // Asigurăm terminatorul de șir
        printf("%s", buffer);
    }

    close(pipefd[0]); // Închidem capătul de citire al tubului

    // Așteptăm procesul copil să termine
    while (wait(NULL) > 0)
        ;

    return EXIT_SUCCESS;
}

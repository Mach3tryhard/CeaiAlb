#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int odd_count = 0, even_count = 0; // Counts for odd and even numbers

void handle_sigusr1(int sig) {
    odd_count++; // Increment odd count on SIGUSR1
}

void handle_sigusr2(int sig) {
    even_count++; // Increment even count on SIGUSR2
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s n number1 number2 ... numberN\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]); // Number of numbers
    if (argc != n + 2) {
        fprintf(stderr, "Error: Provide exactly %d numbers as arguments.\n", n);
        return 1;
    }

    int pipe1[2], pipe2[2]; // Pipes for communication
    pid_t pid1, pid2;       // Process IDs for children

    // Set up signal handling
    signal(SIGUSR1, handle_sigusr1);
    signal(SIGUSR2, handle_sigusr2);

    // Create pipes
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("Pipe creation failed");
        return 1;
    }

    // Fork the first child
    pid1 = fork();
    if (pid1 == 0) {
        // First child process
        close(pipe1[1]); // Close unused write end

        int num;
        while (read(pipe1[0], &num, sizeof(int)) > 0) {
            if (num % 2 != 0) { // Odd number
                kill(getppid(), SIGUSR1); // Notify parent
            }
        }

        close(pipe1[0]);
        exit(0);
    }

    // Fork the second child
    pid2 = fork();
    if (pid2 == 0) {
        // Second child process
        close(pipe2[1]); // Close unused write end

        int num;
        while (read(pipe2[0], &num, sizeof(int)) > 0) {
            if (num % 2 == 0) { // Even number
                kill(getppid(), SIGUSR2); // Notify parent
            }
        }

        close(pipe2[0]);
        exit(0);
    }

    // Parent process
    close(pipe1[0]); // Close unused read end
    close(pipe2[0]); // Close unused read end

    // Send numbers to children
    for (int i = 0; i < n; i++) {
        int num = atoi(argv[i + 2]);
        if (num % 2 == 0) {
            write(pipe2[1], &num, sizeof(int)); // Send to second child
        } else {
            write(pipe1[1], &num, sizeof(int)); // Send to first child
        }
    }

    // Close write ends after sending all data
    close(pipe1[1]);
    close(pipe2[1]);

    // Wait for children to complete
    wait(NULL);
    wait(NULL);

    // Print results
    printf("Odd numbers received: %d\n", odd_count);
    printf("Even numbers received: %d\n", even_count);

    return 0;
}

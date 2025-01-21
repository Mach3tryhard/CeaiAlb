#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

void run_program(const char *program_path, const char *output_file) {
    pid_t pid = fork(); 
    if (pid == 0) {
        int fd = open(output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd == -1) {
            perror("Error opening output file");
            exit(1);
        }
        dup2(fd, STDOUT_FILENO);
        close(fd);

        //execlp(program_path, program_path, (char *) NULL);
        execve(program_path, NULL, NULL);

        exit(1);
    } 
}

void execute_programs_in_directory(const char *dir_path, const char *output_file) {
    DIR *dir = opendir(dir_path);

    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {
            char program_path[1024];
            snprintf(program_path, sizeof(program_path), "%s/%s", dir_path, entry->d_name);

            if (access(program_path, X_OK) == 0) {
                run_program(program_path, output_file);
            }
        }
    }

    closedir(dir);
}

int main(int argc,char *argv[]){
    
    const char *directory = argv[1];
    const char *output_file = argv[2];

    execute_programs_in_directory(directory, output_file);

    return 0;
}

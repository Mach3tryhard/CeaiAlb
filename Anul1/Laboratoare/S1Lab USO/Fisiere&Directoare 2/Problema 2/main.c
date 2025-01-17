#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

int eof(int d){
    int currentOffset = lseek(d, 0, SEEK_CUR);
	if (currentOffset == -1) {
		perror("Error getting file offset");
		close(d);
		return 1;
	}
    struct stat fileInfo;
    if (stat("file.in", &fileInfo) == -1) {
		perror("stat");
		return 1;
	}
    printf("%d\n",currentOffset);
    if(fileInfo.st_size==currentOffset){
        printf("END OF FILE REACHED! :3\n");
    }
}

int main(int argc, char *argv[]){
    int d=open("file.in",O_RDWR);
    if(d<0){
		perror("Error opening file");
		return 1;
	}
    char c;
    ssize_t bytesRead;
    while ( (bytesRead = read(d,&c, 1)) > 0){
        eof(d);   
    }
    return 0;
}
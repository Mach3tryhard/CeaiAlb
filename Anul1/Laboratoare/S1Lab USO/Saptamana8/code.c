#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc,char **argv) {
    int flagf, start, i;
    char *buf;
    struct stat s;
    if(argc>=2 && !strcmp(argv[1],"-e")) {
        flagf=1;
        start=2;
    }
    else{
        flagf=0;
        start=1;
    }
    if(argc<= start){
        fprintf(stderr,"Utilizare: %s [-e] src...\n", argv[0]);
        return 1;
    }
    if(flagf){
        for(i=start;i<argc;++i){
            if((buf = realpath(argv[i],NULL))==NULL){
                continue;
            }
            printf("%s\n",buf);
            free(buf);
        }
    }
    else{
        for(i=start;i<argc;++i){
            do{
                errno=0;buf=NULL;
                if(lstat(argv[i],&s)==-1){
                    break;
                }
                if(S_ISLNK(s.st_mode)) {
                    if((buf=malloc(s.st_size +1))==NULL)
                        break;
                    if(readlink(argv[i],buf,s.st_size)==-1)
                        break;
                    buf[s.st_size]='\0';
                }
                else {
                    break;
                }
            }while(0);
            if(errno) perror(argv[i]);
            free(buf);
        }
    }
    return 0;
}

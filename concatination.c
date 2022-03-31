#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

void doWrite(int fd, const char *buff, int len){

        size_t idx = 0;
        ssize_t wcnt;

        do {
                wcnt = write(fd, buff + idx, len - idx);

                if (wcnt == -1){
                        perror("write");
                        exit(1);
                }

                idx += wcnt;
        } while (idx < len);

}

void write_file(int fd, const char *infile){

        int fd_1 = open(infile, O_RDONLY);

        char buff[1024];
        ssize_t rcnt;

        for (;;){
                rcnt = read(fd_1, buff, sizeof(buff)-1);

                if (rcnt == 0)
                        break;
                if (rcnt == -1){
                        perror("read");
                        exit(1);
                }

                buff[rcnt] = '\0';
                doWrite(fd, buff, strlen(buff));
        }

        close(fd_1);
}

int File_Exists(const char *filename){
        int fd = open(filename, O_RDONLY);
        if(fd != -1){
                close(fd);
                return 1;
        }
        else return 0;
}

int main(int argc, char **argv){

        int fd, oflags, mode;
        mode = S_IRUSR | S_IWUSR;
        oflags = O_CREAT | O_TRUNC | O_WRONLY;

        if(argc < 3 || argc > 4){// Usage error
                printf("Usage: ./fconc infile1 infile2 [outfile (default:fconc.out)]\n");
                exit(1);
        }

        int i = 1;
        while(i <=2){// Entry_file does not exist
                if( !File_Exists(argv[i]) ){
                        if(errno == ENOENT){
                                perror(argv[i]);
                                exit(1);
                        }
                }
                i++;
        }

        if (argv[3] == NULL){// Third argument is absent

                fd = open("fconc.out", oflags, mode);

                write_file(fd, argv[1]);
                write_file(fd, argv[2]);

                close(fd);

               return 0;

        }


        if(strcmp(argv[1], argv[3]) == 0){// First and exit argument are the same

                fd = open(argv[3], O_WRONLY | O_APPEND);

                write_file(fd, argv[2]);
                close(fd);
                return 0;

        }
        else if(strcmp(argv[2], argv[3]) == 0){// Second and exit argument are the same


                int fd_temp = open("temp", oflags, mode);

                write_file(fd_temp, argv[1]);
                write_file(fd_temp, argv[2]);

                fd = open(argv[3], oflags, mode);
                write_file(fd, "temp");
                close(fd);

                remove("temp");

                return 0;

        }

        fd = open(argv[3], oflags, mode);// No error and exit argument provided

        write_file(fd, argv[1]);
        write_file(fd, argv[2]);

        close(fd);

        return 0;
}

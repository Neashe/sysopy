
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#define BUFFER_SIZE 225

void traverse(char* dir_path,char* search_string);

int main(int argc, char *argv[]){
    if (argc !=3){
        fprintf(stderr, "Wrong number of arguments\n");
        exit(EXIT_FAILURE);
    }
    if (strlen(argv[2])>BUFFER_SIZE){
        fprintf(stderr,"String cannot be longer than 225 bytes\n");
        exit(EXIT_FAILURE);
    }

    traverse(argv[1],argv[2]);
    exit(EXIT_SUCCESS);
}

void traverse(char* dir_path,char* given_string){
    pid_t pid = fork();
    struct dirent* dir_entry;
    struct stat file_stat;
    DIR* dir;
    char file_path[PATH_MAX];
    if ((dir = opendir(dir_path)) == NULL){
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    while ((dir_entry = readdir(dir)) != NULL){
        //ignoruj katalog . oraz ..
        if (strcmp(dir_entry->d_name,".")==0 || strcmp(dir_entry->d_name,"..") == 0){
            continue;
        }
        snprintf(file_path,PATH_MAX,"%s/%s",dir_path,dir_entry->d_name);

        if (lstat(file_path, &file_stat)==-1){
            perror("lstat");
            exit(EXIT_FAILURE);
        }
        //jezeli mamy katalog
        if (S_ISDIR(file_stat.st_mode)){
            pid = fork();
            if (pid == -1){
                perror("fork");
                exit(EXIT_FAILURE);
            }
            else if (pid == 0){
                traverse(file_path,given_string);
                exit(EXIT_SUCCESS);
            }
        }

        //jezeli jest to plik
        else{
            FILE* file;
            char * line = NULL;
            size_t len = 0;
            if((file = fopen(file_path,"r"))==NULL){
                perror("fopen");
                exit(EXIT_FAILURE);
            }
            getline(&line,&len,file);
            if (strncmp(line,given_string,strlen(given_string)) == 0){
                printf("PID: %d, %s\n",getpid(), realpath(file_path,NULL));
                fflush(NULL);
            }
            free(line);
            fclose(file);
        }
    }
    if (closedir(dir) == -1){
        perror("closedir");
        exit(EXIT_FAILURE);
    }
}

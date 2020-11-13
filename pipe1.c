#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#define READ 0
#define WRITE 1

int main(){
    int fileDescriptors[2];
    pipe(fileDescriptors);
    pid_t child=fork();
    
    if(child==0){
        char *data="hello";
        close(fileDescriptors[READ]);
        write(fileDescriptors[WRITE], data, strlen(data)+1);
        close(fileDescriptors[WRITE]);
        
    }else{
        wait(NULL);
        char *data=(char *)malloc(sizeof(char)*100);
        close(fileDescriptors[WRITE]);
        read(fileDescriptors[READ], data, 100);
        close(fileDescriptors[READ]);
        printf("The parent received %s\n", data);
        free(data);
    }
    
    return 0;

}
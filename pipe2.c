#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#define READ 0
#define WRITE 1
// ls -la | grep .c is what this code does

int main(){
    int fileDescriptors[2];
    pipe(fileDescriptors);
    pid_t child=fork();
    
    if(child==0){
        close(fileDescriptors[READ]);
        dup2(fileDescriptors[WRITE], STDOUT_FILENO);
        execlp("ls", "ls", "-la", NULL);
        
    } else{
        wait(NULL);
        child=fork();
        if(child==0){
            close(fileDescriptors[WRITE]);
            dup2(fileDescriptors[READ], STDIN_FILENO);
            close(fileDescriptors[READ]);
            execlp("grep", "grep", ".c", NULL);
        }else{
            close(fileDescriptors[WRITE]);
            close(fileDescriptors[READ]);
            wait(NULL);
        }
        
     
    }
    
    return 0;
    
    }
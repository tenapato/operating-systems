// Patricio Tena A01027293
// Francisco Acuña A01027294

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#define READ 0
#define WRITE 1


int main(){
    //Create a socket
     int sock = socket(AF_INET, SOCK_STREAM, 0);
    //Setup the addresses
    struct sockaddr_in addr;
    addr.sin_family=AF_INET;
    addr.sin_port=htons(11809);
    addr.sin_addr.s_addr=INADDR_ANY;
    //Set reutilize
    int allowReuse=1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &allowReuse, sizeof(allowReuse));
    //Bind the socket to the address
    bind(sock, (struct sockaddr *)&addr, sizeof(addr));
    //Listen for connections
    listen(sock, 1);
    //Accept the connect
    int conn = accept(sock, NULL, NULL);
    //Read the connect
    char *buffer=(char *)malloc(5000);
    read(conn, buffer, 5000);
    
   
    if(strncmp(buffer, "turtle", 5)==0){
         write(conn, "ok", strlen("ok")+1);
         
         int option=atoi(&buffer[6]);
         //printf("%d\n", option);
         
         if(option == 1){
             //Start pipe 1
            int fileDescriptors[2];
            pipe(fileDescriptors);
            pid_t child=fork();
    
            if(child==0){
                close(fileDescriptors[READ]);
                dup2(fileDescriptors[WRITE], STDOUT_FILENO);
                execlp("ps", "ps", "-la", NULL);
         }else {
             wait(NULL);
             read(fileDescriptors[READ], buffer, 5000);
             close(fileDescriptors[READ]);
             write(conn, buffer, strlen(buffer));
             close(fileDescriptors[WRITE]);
         } //end of pipe 1
         
        } else if(option == 2){
            //Start of pipe 2
            int fileDescriptors[2];
            pipe(fileDescriptors);
            pid_t child=fork();
    
            if(child==0){
                close(fileDescriptors[READ]);
                dup2(fileDescriptors[WRITE], STDOUT_FILENO);
                execlp("ls", "ls", "-la", NULL);
         }else {
             wait(NULL);
             read(fileDescriptors[READ], buffer, 5000);
             close(fileDescriptors[READ]);
             write(conn, buffer, strlen(buffer));
             close(fileDescriptors[WRITE]);
         } //end of pipe 2
        }
    
    } 
    else{
        //Close
        close(conn);
        close(sock);

    }
    
    
   
    
   
    return 0;
}
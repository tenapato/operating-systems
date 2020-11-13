#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>



int main(){
    //Crate a socket, same as obtaining a file descriptor
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    //Setup the address we want to connect to
    struct sockaddr_in addr;
    addr.sin_family=AF_INET;
    addr.sin_port=htons(11809);
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);  //s going yo connect to a local host
    //Conecting to the address
    connect(sock,(struct sockaddr*)&addr, sizeof(addr));
    //Read and write from the socket
    char *buffer = (char *)malloc(1000);
    strcpy(buffer, "GET / HTTP/1.1\r\n\r\n");
    write(sock, buffer, strlen(buffer));
    //send(sock, buffer, strlen(buffer), 0);
    read(sock, buffer, 1000);
    printf("%s\n", buffer);
    //Close the socket
    close(sock);
    
    
    

    return 0;
}

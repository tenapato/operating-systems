#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


int main(){
mkfifo("home/ubuntu/enviroment/pipe.txt", O_CREAT|0666);
//int pipe = mkfifo("/home/ubuntu/enviroment/pipe.txt", O_CREAT|0666);
int f =  open("/home/ubuntu/enviroment/pipe.txt", O_WRONLY);
char *buffer=(char*)malloc(100);
write(f, buffer, strlen(buffer)+1);
read(f, buffer, 100);
printf("%s", buffer);
close(f);
}
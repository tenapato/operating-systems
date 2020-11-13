  
 #include <stdio.h>
 #include <sys/types.h>
 #include <sys/stat.h>
 #include <string.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <fcntl.h>

int main(){
 mkfifo("/home/ubuntu/environment/pipe.txt", O_CREAT|0666);
 int f= open("/home/ubuntu/environment/pipe.txt", O_RDONLY);
 char *buffer=(char *)malloc(100);
    
    
    while(1){
 
    if(strcmp(buffer, "0") != 0){   
        read(f, buffer, 100);
        
        
        if(strcmp(buffer, "0") != 0){ // para que no imprima si el buffer es 0
            printf("Ingress: %s\n", buffer);
        }
        
        
    }
    else{
       exit(0);
    }
    
    }
    close(f);
    


}
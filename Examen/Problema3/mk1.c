
 #include <stdio.h>
 #include <sys/types.h>
 #include <sys/stat.h>
 #include <string.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <fcntl.h>
 

int main(){
 mkfifo("/home/ubuntu/environment/pipe.txt", O_CREAT|0666);
 int f= open("/home/ubuntu/environment/pipe.txt", O_WRONLY);

 
 while(1){
    
    printf("Options: \n1)Add Patitent 2)EXI\n"); 
    int input;
    scanf("%d", &input);
     
    if(input ==1){
      printf("Name of the patient: \n");
     //char *buffer="John Doe";
     char buffer[5];
    scanf("%s", buffer);
     
     write(f, buffer, strlen(buffer)+1);  
    } 
     else if(input == 2){
       char  *buffer = "0"; 
        write(f, buffer, strlen(buffer)+1);  
        close(f);
        exit(0);
     }
    
     
 }

}

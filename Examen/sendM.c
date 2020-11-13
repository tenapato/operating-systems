 #include <stdio.h>
 #include <sys/types.h>
 #include <sys/ipc.h>
 #include <string.h>
 #include <sys/msg.h>
 #include <stdlib.h>
 struct msgbuf {
               long mtype;       /* message type, must be > 0 */
               char mtext[100];    /* message data */
};

 
 int main(){
   key_t key=ftok("/home/ubuntu/environment/Examen/key.txt", 7);
   int mailbox=msgget(key, IPC_CREAT|0666);
   struct msgbuf m;
   
   
   printf("Order to add: \n");
   char orden[5];
   scanf("%s", orden);
   
   
   
   
   strcpy(m.mtext, orden);
   m.mtype=2;
   msgsnd(mailbox, &m, sizeof(struct msgbuf), 0);
 }
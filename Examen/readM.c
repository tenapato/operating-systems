
 #include <stdio.h>
 #include <sys/types.h>
 #include <sys/ipc.h>
 #include <string.h>
 #include <sys/msg.h>
 
 struct msgbuf {
               long mtype;       /* message type, must be > 0 */
               char mtext[100];    /* message data */
};

 
 int main(){
   key_t key=ftok("/home/ubuntu/environment/Examen/key.txt", 7);
   int mailbox=msgget(key, IPC_CREAT|0666);
   struct msgbuf m;
   int value=msgrcv(mailbox, &m, sizeof(struct msgbuf), 2, IPC_NOWAIT);
   if(value==-1){
    printf("There are not any more orders. You can take a break\n");
   }else{
    printf("The next order to attend is: %s\n", m.mtext);
   }
 }
// Patricio Tena a01027293
// Francisco Acuña a01027294

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>
#define FULLCOUNT 5

int count=0;
_Atomic int pid=0;
pthread_mutex_t queueLock;
sem_t full, empty;
typedef struct Processes{
	int id;
	int remainingTime;
	struct Processes *next;
} Process;

Process *front;

Process *createProcess(int id, int remainingTime){
	Process *toAdd=(Process *)malloc(sizeof(Process));
	toAdd->id=id;
	toAdd->remainingTime=remainingTime;
	toAdd->next=NULL;
	return toAdd;
}
void enqueue(Process *toAdd){
	pthread_mutex_lock(&queueLock);
	if(front==NULL){
		front=toAdd;
	}else{
		Process *temp=front;
		while(temp->next!=NULL){
			temp=temp->next;
		}
		temp->next=toAdd;
	}
	count++;
	pthread_mutex_unlock(&queueLock);
}

Process *dequeue(){
	pthread_mutex_lock(&queueLock);
	Process *toReturn=front;
	front=front->next;
	count--;
	toReturn->next=NULL;
	pthread_mutex_unlock(&queueLock);
	return toReturn;
}

void printQueue(){
	Process *temp=front;
	printf("Total:%d;", count);
	while(temp!=NULL){
			printf("id:%d,rT:%d;",temp->id, temp->remainingTime);
			temp=temp->next;
	}
	printf("\n");
}

void *user(void *args){//producer
	int id=*(int *)args;
	int processesToCreate=(rand()%10)+5;
	for(int i=0; i<processesToCreate; i++){
		sem_wait(&empty); //waits til ampty is different than 0 / decrease the value of empty
        int rTime=rand()%30;
        int currentPid=pid++;
        printf("User %d: created process %d with burst %d\n",id, currentPid, rTime);
        
        enqueue(createProcess(currentPid, rTime));
        sem_post(&full); //increases the value of full by 1
    }
}

void *cpu(void *args){//consumer
	int id=*(int *)args;
	int quantum=5;
	
	
	int counterNoproc= 0;
	
	while(1){
		int result=sem_trywait(&full);
		if(result==-1){//semaphore cannot be decrease, there is no process in the queue
			counterNoproc++;
			if(counterNoproc==3){
				printf("Ready queue empty 3 times for CPU %d. Exiting\n",id);
				//exit(0);
				break;
			}
			
			printf("CPU %d did not found a process in the queue\n", id);
			sleep(5);
			continue;
		}else{
			counterNoproc=0;
		}
	
	
	
	
	
	//while (count != 0){
	
		int r;
	   
	   Process *running = dequeue(); 
	   srand(time(NULL)); 
	   //p[count]=dequeue();
	   //printQueue();
	   printf("Running process %d\n", running->id);
	   for(int i = 0;i < quantum;i++){
	   		r = rand()%100+1;
	    	
	    	
	    	//printf("Random number: %d\n", r);
	    	//Crear I/O blocking
	    	if(r<=10){
	    		//dequeue();
	    		enqueue(running);
	    		
	    		printf("Process %d blocked for I/O and was preempted with remaning time %d\n", running->id, running->remainingTime);
	    		//dequeue();
	    		//running = dequeue();
	    		break;
	    	
	    	} 
	    	
	    	running->remainingTime--;
	       
	    	if(running->remainingTime <=0){
	       	printf("Process %d finished execution\n", running->id);
	       	sem_post(&empty);
	       	break;
	       }
	      
	       
	   }//end of for
		if(running->remainingTime>0 && r > 10){
			//enqueue(running);
			printf("Process %d with time slice %d was preempted with remaining time: %d\n", running->id,quantum, running->remainingTime);
			sem_post(&full);
			//running = dequeue();
		
		}
	    
	   // printQueue();
	    
	    
	    
	   
	    
	}//end of while 
}




int main(){
   
	pthread_t user1, cpu1, user2;
	pthread_mutex_init(&queueLock, NULL);
	sem_init(&full, 0, 0); //initializing the semaphore with 0 spaces in the queue
	sem_init(&empty, 0, FULLCOUNT);
	int id1=1; 
	int id2=2;
	pthread_create(&user1, NULL, user, (void *)&id1);
	//pthread_create(&user2, NULL, user, (void *)&id2);
	pthread_create(&cpu1, NULL, cpu, (void *)&id1);
	pthread_join(user1, NULL);
	//pthread_create(&user2, NULL, user, (void *)&id2);
	//pthread_join(user2, NULL);
	pthread_join(cpu1, NULL);
	return 0;
}
// Patricio Tena A01027293
//Francisco Acuña A01027294

// Lab 7

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int count=0;
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
void enqueue(Process *toAdd){ //recive un apuntador a un proceso
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
}

Process *dequeue(){ //quita el frente de la cola y te da el apuntador a donde esta ese proceso
	Process *toReturn=front;
	front=front->next;
	count--;
	toReturn->next=NULL;
	return toReturn;
}

void printQueue(){  // te dice que hay en la cola
	Process *temp=front;
	printf("Total:%d;", count);
	while(temp!=NULL){
			printf("id:%d,rT:%d;",temp->id, temp->remainingTime);
			temp=temp->next;
	}
	printf("\n");
}

int main(){
    int quantum = 5;
    
    //p->remaningTime-quantum en un for
    //p->remaningTime--//generar random entre 0-100 y si es<10, preemtion por I/O
    /*
	printQueue();
	enqueue(createProcess(1, 10));
	Process *p1=createProcess(2, 20);
	enqueue(p1);
	printQueue();
	Process *p=dequeue();
	printf("Sacado %d con tiempo %d\n", p->id, p->remainingTime);
	p=dequeue();
	printf("Sacado %d con tiempo %d\n", p->id, p->remainingTime);
	printQueue();*/
	
	Process *p1=createProcess(1, 20);
	enqueue(p1);
	printf("Adding process %d with running time: %d\n", p1->id, p1->remainingTime);
	Process *p2=createProcess(2, 7);
	enqueue(p2);
	printf("Adding process %d with running time: %d\n", p2->id, p2->remainingTime);
	Process *p3=createProcess(3, 15);
	enqueue(p3);
	printf("Adding process %d with running time: %d\n", p3->id, p3->remainingTime);
	Process *p4=createProcess(4, 10);
	enqueue(p4);
	printf("Adding process %d with running time: %d\n", p4->id, p4->remainingTime);
	Process *p5=createProcess(5, 12);
	enqueue(p5);
	printf("Adding process %d with running time: %d\n", p5->id, p5->remainingTime);
	
	srand(time(NULL));  
	while (count != 0){
		 
		int r;
	   
	   Process *running = dequeue(); 
	   //p[count]=dequeue();
	   //printQueue();
	   printf("Running process %d\n", running->id);
	   for(int i = 0;i < quantum;i++){
	   		r = rand()%100+1;
	    	
	    	
	    //	printf("Random number: %d\n", r);
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
	       	break;
	       }
	      
	       
	   }//end of for
		if(running->remainingTime>0 && r > 10){
			//enqueue(running);
			printf("Process %d with time slice %d was preempted with remaining time: %d\n", running->id,quantum, running->remainingTime);
			//running = dequeue();
		
		}
	    
	   // printQueue();
	    
	    
	    
	    
	    
	}//end of while 
	
	
	
	
	
	
	
	
	
	
	return 0;
}
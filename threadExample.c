//para compilar gcc threadExample.c -lpthread
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>


struct arguments{
    int i;
    int j;
};


void *function(void *arg){
    //int value=*(int *)arg;
    struct arguments *value=(struct arguments *)arg;
    printf("I: %d\n J:%d\n", value->i, value->j);
}





int main(){
    printf("Hello from main \n");
   /* int a=1;
    int b=2;
    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, function,(void *)&a);
    pthread_create(&tid2, NULL, function,(void *)&b);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    */
    
    pthread_t tid1;
    struct arguments *args=(struct arguments *)malloc(sizeof(struct arguments));
    args->i=1;
    args->j=2;
    pthread_create(&tid1, NULL, function, (void *)args);
    pthread_join(tid1, NULL);
    
    
    
    
   /* pthread_create(// function to create a thread
        pthread_t *thread, //thread id
        const pthread_attr_t *attr,  //attributes of the thread
        void *(*start_routine) (void *),//function (a void pointer without any type)
        void  *arg); //arguments of the fucntion
        function();
    */
    
    
    //free(value);
    return 0;
}
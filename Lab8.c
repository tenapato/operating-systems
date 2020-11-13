// Patricio Tena A01027293
// Francisco Acuña A01027294


#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>


#define M 3
#define N 3
#define O 3

int A[M][N] = {{1,2,3}, {4,5,6}, {7,8,9}};
int B[M][N] = {{1,1,1}, {1,1,1}, {1,1,1}};
int C[M][N];

void printResultado(){
    for(int i =0; i<M; i++){
        for(int j = 0; j<N; j++){
            printf("%d, ",C[i][j]);
        }
        printf("\n");
    }
    
}


struct arguments{
  int i;
  int j;

};



void *multiplicar(void *args){
    struct arguments *matrixArgs=(struct arguments *)args; //castear el tipo que va a ser el apuntador
   // C[matrixArgs->i][matrixArgs->j] = A[matrixArgs->i][matrixArgs->j] * B[matrixArgs->i][matrixArgs->j];
   C[matrixArgs->i][matrixArgs->j]= 0;
   
   for(int k = 0; k<O; k++){
       C[matrixArgs->i][matrixArgs->j] += A[matrixArgs->i][k] * B[k][matrixArgs->j];
   }
   
   
    free(args);
}



int main(){
    
    pthread_t tids[M][N];
    for(int i =0; i<M; i++){
        for(int j = 0; j<N; j++){
            
                struct arguments *args=(struct arguments *)malloc(sizeof(struct arguments));
                args->i=i;
                args->j=j;
                
                pthread_create(&tids[i][j], NULL, multiplicar, (void *) args);
            
        }
    }
    
    //hacer un for de i hasta M para esperarpor los joins
        //for de j hasta N
    for(int i =0; i<M; i++){
        for(int j = 0; j<N; j++){
    pthread_join(tids[i][j], NULL);
    
        }
    }
    printResultado();
    return 0;
}
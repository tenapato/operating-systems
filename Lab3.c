  /*
    d = enteros
    f = float/double
    c = char
    s = string
    p = pointer
    */

//Patricio Tena A01027293 , Francisco Acuña A01027294

#include <stdio.h>
#include <stdlib.h>

int ejercicio3(int a){
    int h = 10;
    int *k=&h;
    
    printf("%d\n", *k);
    k--;
     printf("%d\n", *k);
    k--;
     printf("Parameter: %d\n", *k);
  

// -fno-stack-protector

}


void ejercicio1(){
    int a = 5;
    int *b=&a;
    char a2 = 'b';
    char *b2 = &a2;
    float a3 = 7.55;
    float *b3 = &a3;
    
      //Para el int
    printf("Int: \n");
    printf("Content: %d, Address: %p, Size: %ld\n", a, &a, sizeof(a));
    printf("Content: %p, Address: %p, Size: %ld\n", b, &b, sizeof(b));
    
    //Para el char
    printf("Char: \n");
    printf("Content: %c, Address: %p, Size: %ld\n", a2, &a2, sizeof(a2));
    printf("Content: %p, Address: %p, Size: %ld\n", b2, &b2, sizeof(b2));
    
    //Para el float
    printf("Char: \n");
    printf("Content: %f, Address: %p, Size: %ld\n", a3, &a3, sizeof(a3));
    printf("Content: %p, Address: %p, Size: %ld\n", b3, &b3, sizeof(b3));
    
    
}

void ejercicio2(){
    int *c=(int *)malloc(10*sizeof(int)); //malloc le pide al sistema operativo una cierta cantidad de bytes en la memoria
    c[1]=3;
    printf("Content: %d, Adress: %p, Size %ld\n", c[1], &c, sizeof(*c) );
    
    
}



int main(){

  
    //Ejercicio 1
    printf("Ejercicio 1\n");
    ejercicio1();
    
  
    
    //Ejercicio 2
    printf("\n");
    printf("Ejercicio 2\n");
    ejercicio2();
    
  
    
    
    //Ejercicio 3
    printf("\n");
    printf("Ejercicio 3\n");
    
    ejercicio3(5); //para este se necesita compilar de la sig forma: gcc first.c -fno-stack-protector
    
    return 0;
    
}
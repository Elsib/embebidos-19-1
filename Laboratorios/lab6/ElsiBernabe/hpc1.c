
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
//#define NUM_HILOS 4
#define N 64 //Con números grandes hay problemas con la sinconía pero 

//programa para crear muchos hilos

int *A, *B, *C;
int * reservarMemoria();
void llenarArreglo(int *datos);
void imprimirArreglo(int *datos);
void producto(void );


void * funHilo(void *arg);
pthread_mutex_t bloqueo;

int contador;

int main(){

	srand(getpid()); //Semilla para generar random del número de proceso

	A = reservarMemoria();
	llenarArreglo(A);
	imprimirArreglo(A);
	
	B = reservarMemoria();
	llenarArreglo(B);
	imprimirArreglo(B);
	
	C = reservarMemoria();
	producto();
	imprimirArreglo(C);
	
	free(A);
	free(B);
	free(C);

	return 0;
}


int * reservarMemoria(){
	int *mem;

	mem = (int *) malloc(sizeof(int)*N);
	if(!mem){
		perror("Error al asignar memoria...\n");
		exit(EXIT_FAILURE);
	}

	return mem;
}


void llenarArreglo(int *datos){
	register int i;

	for(i = 0; i < N; i++){
		datos[i] = rand() % 255;
	}
}


void producto(void){
	register int i;

	for(i = 1; i < N; i++){
		C[i] = A[i] * B[i];
	}
}


void imprimirArreglo(int *datos){
	register int i;

	for(i = 0; i < N; i++){

		if(!(i%8))
			printf("\n");

		printf("%3d ", datos[i]);
	}
	printf("\n");
}

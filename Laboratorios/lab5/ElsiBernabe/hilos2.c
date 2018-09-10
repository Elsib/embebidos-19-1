#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define N 32

int * reservarMemoria();
void llenarArreglo(int *datos);
void imprimirArreglo(int *datos);
void * mayorArreglo(void *arg);
void * menorArreglo(void *arg);


int main(){
	int *res_may, *res_men, *datos;
	pthread_t tid_may, tid_men;

	printf("Probando hlos...\n");

	datos = reservarMemoria();
	llenarArreglo(datos);
	imprimirArreglo(datos);

	pthread_create(&tid_men, NULL, menorArreglo, datos);
	pthread_create(&tid_may, NULL, mayorArreglo, datos);


	pthread_join(tid_men, (void **)&res_men);
	pthread_join(tid_may, (void **)&res_may);


	printf("El menor es: %d\n", *res_men);
	printf("El mayor es: %d\n", *res_may);

	return 0;
}



void llenarArreglo(int *datos){
	register int i;

	srand(getpid()); //Semilla para generar random del número de proceso

	for(i = 0; i < N; i++){
		datos[i] = rand() % 255;
	}
}

int * reservarMemoria()
{
	int * mem;
	mem = (int *) malloc(sizeof(int)*N);
	if (!mem)
	{
		perror("Error al asignar memoria...\n");
		exit(EXIT_FAILURE);
	}
}

void imprimirArreglo(int *datos){
	register int i;

	for(i = 0; i < N; i++){

		if(!(i%16))
			printf("\n");

		printf("%3d ", datos[i]);
	}
	printf("\n");
}

void * menorArreglo(void *arg){
	static int menor;
	register int i;
	int *datos = (int *)arg;
	menor = datos[0];

	for(i = 1; i < N; i++){
		if(datos[i]<menor)
			menor = datos[i];
	}
	pthread_exit((void *)&menor);
}

void * mayorArreglo(void *arg){
	static int mayor;
	register int i;
	int *datos = (int *)arg;
	mayor = datos[0];

	for(i = 1; i < N; i++){
		if(datos[i]>mayor)
			mayor = datos[i];
	}

	pthread_exit((void *)&mayor);
}
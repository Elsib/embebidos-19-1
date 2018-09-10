#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define NUM_HILOS 4

/*int * reservarMemoria();
void llenarArreglo(int *datos);
void imprimirArreglo(int *datos);
void * mayorArreglo(void *arg);
void * menorArreglo(void *arg);
*/
void * funHilo(void *arg);
pthread_mutex_t bloqueo;

int contador;
int main(){
	int nhs[NUM_HILOS], *res;
	register int nh;
	pthread_t tids[NUM_HILOS];
	contador = 0;
	pthread_mutex_init(&bloqueo, NULL);
	printf("Probando hlos...\n");

	/*
	datos = reservarMemoria();
	llenarArreglo(datos);
	imprimirArreglo(datos);
	*/
	for (nh = 0; nh < NUM_HILOS; nh++)
	{
		nhs[nh] = nh;
		pthread_create(&tids[nh], NULL, funHilo, (void *)&nhs[nh]);
	}

	for (nh = 0; nh < NUM_HILOS; nh++)
	{
		pthread_join(tids[nh], (void **)&res);
		printf("Hilo %d terminado\n", *res);
	}

	pthread_mutex_destroy(&bloqueo);
	return 0;
}

void * funHilo(void *arg){
	int nh = *(int *)arg;
	register int i = 0;

	pthread_mutex_lock(&bloqueo);
	contador ++;
	printf("Iniciando hilo %d con contador %d \n", nh, contador );
	while((--i));
	//sleep(5);
	printf("terminando hilo %d con contador %d \n", nh, contador );
	pthread_mutex_unlock(&bloqueo);

	pthread_exit( arg );
}



/*

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
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#define N 32

int * reservarMemoria();
void llenarArreglo(int *datos);
void imprimirArreglo(int *datos);
int mayorArreglo(int *datos);
int menorArreglo(int *datos);

int main(){
	int *datos, mayor, menor;

	datos = reservarMemoria();
	llenarArreglo(datos);
	imprimirArreglo(datos);

	mayor = mayorArreglo(datos);
	menor = menorArreglo(datos);

	printf("El número mayor es: %d \n", mayor);
	printf("El número menor es: %d \n", menor);

	free(datos);

	return 0;

}

int mayorArreglo(int *datos){
	register int i , mayor;

	mayor = datos[0];

	for(i = 1; i < N; i++){
		if(datos[i]>mayor)
			mayor = datos[i];
	}

	return mayor;
}

int menorArreglo(int *datos){
	register int i , menor;

	menor = datos[0];

	for(i = 1; i < N; i++){
		if(datos[i]<menor)
			menor = datos[i];
	}

	return menor;
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
//Compilar: gcc datos-c -o datos
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#define NUM_PROC 4
#define N 5

int * reservarMemoria();
void llenarArreglo(int *datos);
void imprimirArreglo(int *datos);
int mayorArreglo(int *datos);
int menorArreglo(int *datos);
int promedioArreglo(int *datos);
void ordenaArreglo(int *datos);

void procesoHijo(int np, int * datos, int pipefd[]);
void procesoPadre(int pipefd[]);

int main(){
	pid_t pid;
	int np;

	int *datos, pipefd[4], pipe_status;

	datos = reservarMemoria();
	llenarArreglo(datos);
	imprimirArreglo(datos);

	printf("Probando procesos...\n");
	pipe_status = pipe(pipefd);
	
	if (pipe_status == -1)
	{
		perror("Error al crear la tubería...\n");
		exit(EXIT_FAILURE);
	}

	for (np = 0; np < NUM_PROC; np++)
	{
	
		pid = fork();
		if (pid== -1)
		{
			perror("No se creó el proceso... \n");
			exit(EXIT_FAILURE);
		}
		//Tiene pid = 0 es hijo, pid > 0 es padre
		if(!pid){
			procesoHijo(np, datos, pipefd);
		}	
	}
	procesoPadre(pipefd);	

	free(datos);
	return 0;
}


void procesoPadre(int pipefd[])
{
	int np, npc, numero;
	pid_t pid_hijo;

	printf("Proceso padre ejecutado con pid %d\n", getpid());
	
	close(pipefd[1]);
	for (np=0; np<NUM_PROC;np++)
	{
		pid_hijo=wait(&npc);
		npc = npc>>8;
		read(pipefd[0], &numero, sizeof(int));
		if (npc==0)
		{
			printf("Proceso hijo %d terminado con pid: %d y mayor %d\n", npc, pid_hijo, numero);	
		}else if(npc==1){
			printf("Proceso hijo %d terminado con pid: %d y menor %d\n", npc, pid_hijo, numero);
		}else if(npc==2){
			printf("Proceso hijo %d terminado con pid: %d y promedio %d\n", npc, pid_hijo, numero);
		}else
			printf("Proceso hijo %d terminado con pid: %d\n", npc, pid_hijo);
	}
	close(pipefd[0]);
}

void procesoHijo(int np, int * datos, int pipefd[])
{
	int mayor, menor, promedio; 
	//float promedio;
	printf("Proceso hijo %d ejecutado con pid %d\n", np, getpid());
//	while(1);
	if(np==0)
	{
		close(pipefd[0]);
		mayor = mayorArreglo(datos);
		write(pipefd[1], &mayor, sizeof(int));
		close(pipefd[1]);
		exit(np);
	}else if (np==1)
	{
		close(pipefd[0]);
		menor = menorArreglo(datos);
		write(pipefd[1], &menor, sizeof(int));
		close(pipefd[1]);
		exit(np);
	}else if (np==2)
	{
		promedio = promedioArreglo(datos);
		//printf("promedio:%f\n", promedio);
		write(pipefd[1], &promedio, sizeof(int));
		close(pipefd[1]);
		exit(np);
	}else if (np==3)
	{
		close(pipefd[0]);
		ordenaArreglo(datos);
		imprimirArreglo(datos);
		close(pipefd[1]);
		exit(np);
	}

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
	return mem;
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

int menorArreglo(int *datos){
	register int i , menor;

	menor = datos[0];

	for(i = 1; i < N; i++){
		if(datos[i]<menor)
			menor = datos[i];
	}

	return menor;
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

int promedioArreglo(int *datos){
	register int i, suma, prom;
	//float prom;
	suma=0;
	prom = 0.0;

	for(i = 0; i < N; i++){
		suma = suma + datos[i];
	}

	prom = suma/N;

	return prom;
}

void ordenaArreglo(int *datos){
	register int i, j, imin, aux;

	//Método de Selección
	for(i = 0; i < N-1; i++){
		imin = i;

		for (j = i+1; j < N; j++)
		{
			if(datos[j] < datos[imin]){
				imin = j;
			}
		}
		//intercambia i con imin
		aux = datos[i];
		datos[i] = datos[imin];
		datos[imin] = aux;

	}
}

//Crear otro proceso que encuentre los datos y otro proceso que los ordene
//Procesamiento.c --> pomer todas las funciones que hacen el procesamiento
//Procesos.c --> Código de proces hojo y proceso padre
//Proncipal.c --> función main()

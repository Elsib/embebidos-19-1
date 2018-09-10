#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#include "defs.h"
#include "procesamiento.h"
#include "datos.h"

void procesoPadre(int pipefd[])
{
	int np, npc, numero, ordena[N];
	pid_t pid_hijo;

	printf("Proceso padre ejecutado con pid %d\n", getpid());
	
	close(pipefd[1]);
	for (np=0; np<NUM_PROC;np++)
	{
		pid_hijo=wait(&npc);
		npc = npc>>8;
		//read(pipefd[0], &numero, sizeof(int));
		if (npc==0)
		{
			read(pipefd[0], &numero, sizeof(int));
			printf("Proceso hijo %d terminado con pid: %d y mayor %d\n", npc, pid_hijo, numero);	
		}else if(npc==1){
			read(pipefd[0], &numero, sizeof(int));
			printf("Proceso hijo %d terminado con pid: %d y menor %d\n", npc, pid_hijo, numero);
		}else if(npc==2){
			read(pipefd[0], &numero, sizeof(int));
			printf("Proceso hijo %d terminado con pid: %d y promedio %d\n", npc, pid_hijo, numero);
		}else{
			read(pipefd[0], &ordena, sizeof(int)*N);
			printf("Proceso hijo %d terminado con pid: %d\n y retorno \n:", npc, pid_hijo);
		}
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
		write(pipefd[1], datos, sizeof(int)*N);
		imprimirArreglo(datos);
		close(pipefd[1]);
		exit(np);
	}

}
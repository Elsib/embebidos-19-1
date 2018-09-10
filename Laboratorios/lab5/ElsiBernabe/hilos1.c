#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void * suma (void * arg);
void * resta (void * arg);
void * multi (void * arg);
void * divi (void * arg);
int num1 = 52, num2 = 10;


int main(){
	int *res_sum, *res_res, *res_mul, *res_div;
	pthread_t tid_sum, tid_res, tid_mul, tid_div;

	printf("Probando hlos...\n");
	pthread_create(&tid_sum, NULL, suma, NULL);
	pthread_create(&tid_res, NULL, resta, NULL);
	pthread_create(&tid_mul, NULL, multi, NULL);
	pthread_create(&tid_div, NULL, divi, NULL);

	pthread_join(tid_sum, (void **)&res_sum);
	pthread_join(tid_res, (void **)&res_res);
	pthread_join(tid_mul, (void **)&res_mul);
	pthread_join(tid_div, (void **)&res_div);

	printf("La suma es: %d\n", *res_sum);
	printf("La resta es: %d\n", *res_res);
	printf("La multiplicación es: %d\n", *res_mul);
	printf("La división es: %d\n", *res_div);
	return 0;
}



void * suma (void * arg){
	int *res = (int *)malloc(sizeof(int));

	*res = num1 + num2;
	pthread_exit((void *)res);
}

void * resta (void * arg){
	int *res = (int *)malloc(sizeof(int));

	*res = num1 - num2;
	pthread_exit((void *)res);
}

void * multi (void * arg){
	static int res;

	res = num1 * num2;
	pthread_exit((void *)&res);
}

void * divi (void * arg){
	static int res;

	res = num1 / num2;
	pthread_exit((void *)&res);
}

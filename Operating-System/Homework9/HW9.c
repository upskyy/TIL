#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t m_lock = PTHREAD_MUTEX_INITIALIZER;

int total = 0;

void *factorial(void *number) {
	int factorial_cal = 1;
	int *num = (int *)number;
	for (int i = 1; i <= *(num); i++) {
		factorial_cal *= i;
	}
	printf("%d! : %d\n", *num, factorial_cal);
	pthread_mutex_lock(&m_lock);
	total += factorial_cal;
	pthread_mutex_unlock(&m_lock);
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Please put one argument.\n");
		return 0;
	}
	int num;
	num = atoi(argv[1]);

	pthread_t thread_id[num];
	int *array = (int *)malloc(num * sizeof(int));
	for (int i = 0; i < num; i++) {
		array[i] = i + 1;
	}
	for (int i = 0; i < num; i++) {
		pthread_create(&thread_id[i], NULL, factorial, (void *)&array[i]);
	}
	for (int i = 0; i < num; i++) {
		pthread_join(thread_id[i], NULL);
	}
	free(array);
	pthread_mutex_destroy(&m_lock);
	
	printf("total : %d\n", total);
	return 0;
}
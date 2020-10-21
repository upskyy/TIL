#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define random_number() rand()%101

int main() {
	int array[101] = { 0, };
	int max_value = 0;
	int max_count = 0;
	srand(time(NULL));
	for (int i = 0; i < 100; i++) {
		array[random_number()]++;
	}
	for (int i = 0; i < 101; i++) {
		if (max_count < array[i]) {
			max_value = i;
			max_count = array[i];
		}
	}
	printf("Most occurred number : %d\n", max_value);
	printf("Number of occurrences : %d\n", max_count);

	/*  result check
	for (int i = 0; i < 101; i++) {
		printf("%d  ", array[i]);
	}
	*/

	return 0;
}
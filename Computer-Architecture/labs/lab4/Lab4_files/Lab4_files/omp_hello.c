#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// Function prototype
void hello(void);

int main(int argc, char *argv[]) {
	
	// Get number of threads from the command line
	int thread_count = strtol(argv[1], NULL, 10);
	
	// OpenMP parallel threads using pragma directive
	#pragma omp parallel num_threads(thread_count)
	hello();
	
	return 0;
}

void hello(void) {
	// Get parameters from OpenMP function calls
	int thread_id = omp_get_thread_num();
	int thread_count = omp_get_num_threads();
	
	printf("Hello from thread %d of %d\n", thread_id, thread_count);
}
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
 
#define ARRAYSIZE 100000000 // Array size

// Initialize data array
double data[ARRAYSIZE];

int main(int argc, char *argv[]) {
	
	// Get number of threads
	int thread_count = 1;
	if (argc > 1) thread_count = atoi(argv[1]);
	
	// Initialize the data
	for (int i = 1; i <= ARRAYSIZE; i++) {
		data[i] = i * 1.0;
	}
	
	// Get start time to measure serial process elapsed time
	double start_time = omp_get_wtime();
	
	// Execute serial addtion
	double serial_sum = 0.0;
	for (int i = 0; i < ARRAYSIZE; i++) {
		serial_sum = serial_sum + data[i];
	}
		
	printf("\n*** Serial sum = %e\n\n", serial_sum);
		
	// Get final time and compute total elapsed time of serial process
	double elapsed_ser = omp_get_wtime() - start_time;
	
	printf(">> Serial time = %f seconds\n\n", (float)elapsed_ser);
	
	// Get start time to measure parallel process elapsed time
	start_time = omp_get_wtime();
	
	// Execute parallel addition and reduction using OpenMP pragma directive
	double parallel_sum = 0.0;
	# pragma omp parallel for num_threads(thread_count) \
		reduction(+: parallel_sum) shared(data)
	for (int i = 0; i < ARRAYSIZE; i++) {
		parallel_sum = parallel_sum + data[i];
	}
		
	printf("\n*** Parallel sum = %e\n\n", parallel_sum);
	
	// Get final time and compute total elapsed time of parallel process
	double elapsed_par = omp_get_wtime() - start_time;
	
	printf(">> Parallel time = %f seconds\n", (float)elapsed_par);
	
	return 0;
}
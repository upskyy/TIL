#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define POINTS 200000 // Number of random points
#define ROUNDS 1000   // Iteration per number of random point selection

// Built-in stdlib.h random generator functions
void srandom (unsigned seed); // Input seed for random() function
long random(void);            // Outputs a random 32 bit number
// Function prototype
double compute_pi(int points);

int main(int argc, char *argv[]) {
	
	// Get number of serial tasks 
	int thread_count = 1;
	if (argc > 1) thread_count = atoi(argv[1]);
	
	// Seed random number generator for serial process
	srandom(thread_count + 1);
	
	// Define variables for computation
	double proc_pi, sum_pi, pi, ave_pi;
	
	printf("***Start serial process...\n");
	
	// Get start time to measure serial process elapsed time
	double start_time = omp_get_wtime();
	
	for (int i = 0; i < ROUNDS; i++) {
		
		sum_pi = 0.0;
		for (int task = 0; task < thread_count; task++) {
			// Compute Pi per task distribution using the Monte Carlo estimation
			proc_pi = compute_pi(POINTS);
			sum_pi = sum_pi + proc_pi;
		}
		
		pi = sum_pi / thread_count;
		ave_pi = ((ave_pi * i) + pi) / (i + 1); // Compute moving average
		if ((i + 1) % 100 == 0) // Show result per 100 iteration
			printf("   After %9d points, average value of pi = %10.8f\n",
				(POINTS * thread_count * (i + 1)), ave_pi);
	}
	
	// Get final time and compute total elapsed time of serial process
	double elapsed_ser = omp_get_wtime() - start_time;
	
	printf(">> Serial time = %f seconds\n", (float)elapsed_ser);
	
	printf("\n***Start parallel process...\n");
	
	// Seed random number generator for parallel process
	srandom(thread_count + 2);
	
	// Get start time to measure parallel process elapsed time
	start_time = omp_get_wtime();
	
	ave_pi = 0.0; // Re-initialize variable
	for (int i = 0; i < ROUNDS; i++) {
		
		// Execute parallel function call and reduction using OpenMP pragma directive
		sum_pi = 0.0;
		# pragma omp parallel for num_threads(thread_count) \
			reduction(+: sum_pi) private(proc_pi)
		for (int task = 0; task < thread_count; task++) {
			// Compute Pi per task distribution using the Monte Carlo estimation
			proc_pi = compute_pi(POINTS);
			sum_pi = sum_pi + proc_pi;
		}
		
		pi = sum_pi / thread_count;
		ave_pi = ((ave_pi * i) + pi) / (i + 1); // Compute moving average
		if ((i + 1) % 100 == 0) // Show result per 100 iteration
			printf("   After %9d points, average value of pi = %10.8f\n",
				(POINTS * thread_count * (i + 1)), ave_pi);
	}

	// Get final time and compute total elapsed time of serial process
	double elapsed_par = omp_get_wtime() - start_time;
	
	printf(">> Parallel time = %f seconds\n", (float)elapsed_par);
	
	printf("\nReal value of PI: 3.1415926535897 \n");
	
	return 0;
}

// Monte Carlo method of approximating Pi
double compute_pi(int points) {
	
	double x_coord, y_coord , rnd;
	
	// Maximum random number from generator -
	// - to scale random number between 0 and 1
	double max_rand = 2147483647; // Equal to ((2^31)-1)
	
	// Initialize M variable
	int m_score = 0;
	
	// Generate N samples
	for (int n = 1; n <= points; n++) {
		// Generate random point with x and y coordinates
		rnd = (double)random() / max_rand;
		x_coord = (2.0 * rnd) - 1.0; // Rescale between -1 and +1
		rnd = (double)random() / max_rand;
		y_coord = (2.0 * rnd) - 1.0; // Rescale between -1 and +1
		
		// Check whether the point is inside the circle of radius 1
		// It should satisfy this inequality (x_coord)^2 + (y_coord)^2 <= (r=1)^2
		if ((x_coord * x_coord) + (y_coord * y_coord) <= 1.0)
			m_score++; // Append 1 if it satisfies the inequality
	}
	
	// Compute Pi value
	double pi = 4.0 * (double)m_score / (double)points;
	return pi;
}
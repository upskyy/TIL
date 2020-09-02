#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mpi.h"

#define POINTS 200000 // Number of random points
#define ROUNDS 1000   // Iteration per number of random point selection
#define MASTER 0      // Task id of MASTER

// Built-in stdlib.h random generator functions
void srandom (unsigned seed); // Input seed for random() function
long random(void);            // Outputs a random 32 bit number
// Function prototype
double compute_pi(int points);

int main(int argc, char *argv[]) {
	
	// Initialize MPI environment
	MPI_Init(&argc, &argv);
	
	// Get the number of tasks
	int numtasks;
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	
	// Get the task id
	int taskid;
	MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
	printf ("MPI task %d has started...\n", taskid);
	
	// Status for MPI_Recv 
	MPI_Status status;
	
	// Seed random number generator for each task
	srandom(taskid);
	
	// Define variables for local task
	double proc_pi, sum_pi, pi, ave_pi;
	
	// Barrier for synchronization
	// Begin only after all tasks are initialized
	MPI_Barrier(MPI_COMM_WORLD);
	
	// Execute serial Pi computation on MASTER task only
	if (taskid == MASTER) {
		
		// Get start time to measure serial process elapsed time
		clock_t t; 
		t = clock();
		
		printf("\n***Start serial process...\n");
		
		for (int i = 0; i < ROUNDS; i++) {
		
			sum_pi = 0.0;
			for (int task = 0; task < numtasks; task++) {
				// Compute Pi per task distribution using the Monte Carlo estimation
				proc_pi = compute_pi(POINTS);
				sum_pi = sum_pi + proc_pi;
			}
		
			pi = sum_pi / numtasks;
			ave_pi = ((ave_pi * i) + pi) / (i + 1); // Compute moving average
			if ((i + 1) % 100 == 0) // Show result per 100 iteration
				printf("   After %9d points, average value of pi = %10.8f\n",
					(POINTS * numtasks * (i + 1)), ave_pi);
		}
		
		// Get final time and compute total elapsed time of serial process
		t = clock() - t;
		double elapsed_ser = ((double)t)/CLOCKS_PER_SEC;
		
		printf("\n>> Serial time = %f seconds\n", (float)elapsed_ser);
		
		printf("\n***Start parallel process...\n");
	}
	
	// Barrier for synchronization
	// Begin only after serial process in done
	MPI_Barrier(MPI_COMM_WORLD);
	
	// Get start time to measure parallel process elapsed time
	double w1 = MPI_Wtime();
	
	ave_pi = 0.0; //Reinitialize value
	for (int i = 0; i < ROUNDS; i++) {
		
		// All tasks will compute Pi using the Monte Carlo estimation
		proc_pi = compute_pi(POINTS);
		
		// Use MPI reduce to sum values of proc_pi across all tasks
		MPI_Reduce(&proc_pi, &sum_pi, 1, MPI_DOUBLE, MPI_SUM, 
		           MASTER, MPI_COMM_WORLD);
				   
		// MASTER computes the average Pi value for all iteration
		if (taskid == MASTER) {
			pi = sum_pi / numtasks;
			ave_pi = ((ave_pi * i) + pi) / (i + 1); // Compute moving average
			if ((i + 1) % 100 == 0) // Show result per 100 iteration
				printf("   After %9d points, average value of pi = %10.8f\n",
					(POINTS * numtasks * (i + 1)), ave_pi);
		}
	}
	
	// Get final time and compute total elapsed time of parallel process
	double w2 = MPI_Wtime();
    double local_time = w2 - w1;
    double elapsed;
    MPI_Reduce(&local_time, &elapsed, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
	
	// MASTER task only
	if (taskid == MASTER) {
		printf("\n>> Parallel time = %f seconds\n", (float)elapsed);
		// Display rela value of Pi for reference
		printf("\nReal value of PI: 3.1415926535897 \n"); 
	}
	
	// Finalize MPI environment
	MPI_Finalize();
	
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
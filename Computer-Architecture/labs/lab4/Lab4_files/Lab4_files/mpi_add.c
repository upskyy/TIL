#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include "mpi.h"

#define ARRAYSIZE 100000000 // Array size
#define MASTER    0         // Task id of MASTER

// Initialize data array
double data1[ARRAYSIZE];
double data2[ARRAYSIZE];

// Function prototype
double compute_sum(int offset, int chunksize, int taskid);

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
	
	// Compute equal data chunk size for each task
	int chunksize = ARRAYSIZE / numtasks;
	int leftover = ARRAYSIZE % numtasks;
	
	// Initialize message tags
	int tag1 = 1;
	int tag2 = 2;
	int tag3 = 3;
	
	// Define variable for local task
	int offset;
	
	// MASTER task only
	if (taskid == MASTER) {
		
		// Initialize the data by MASTER only
		for (int i = 1; i <= ARRAYSIZE; i++) {
			data1[i] = i * 1.0;
			data2[i] = i * 1.0;
		}
		
		// Get start time to measure serial process elapsed time
		clock_t t; 
		t = clock();
		
		// Execute serial addtion
		double serial_sum = 0.0;
		double temp = 0.0;
		for (int i = 0; i < ARRAYSIZE; i++) {
			temp = data1[i] * data2[i];
			serial_sum = serial_sum + temp;
		}
		
		printf("\n*** Serial sum = %e\n\n", serial_sum);
		
		// Get final time and compute total elapsed time of serial process
		t = clock() - t;
		double elapsed_ser = ((double)t)/CLOCKS_PER_SEC;
	
		printf(">> Serial time = %f seconds\n\n", (float)elapsed_ser);
	}
	


	// Get start time to measure parallel process elapsed time
	double w1 = MPI_Wtime();
	
	// MASTER task only
	if (taskid == MASTER) {
		
		// Send each portion of the array to each task while -
		// - the MASTER keeps the 1st part plus leftover
		offset = chunksize + leftover;
		for (int dest_id = 1; dest_id < numtasks; dest_id++) {
			// Send offset value to NON-MASTER
			MPI_Send(&offset, 1, MPI_INT, dest_id, tag1, MPI_COMM_WORLD);
			// Send data value to NON-MASTER
			MPI_Send(&data1[offset], &data2[offset], chunksize, MPI_DOUBLE, dest_id, tag2, MPI_COMM_WORLD);
			offset = offset + chunksize;
		}

		// Do summation for MASTER
		offset = 0;
		double sum = compute_sum(offset, chunksize + leftover, taskid);
		
		// Wait to receive results from all NON-MASTER
		 for (int source_id = 1; source_id < numtasks; source_id++) {
			// Receive offset value from NON-MASTER
			MPI_Recv(&offset, 1, MPI_INT, source_id, tag1, MPI_COMM_WORLD, &status);
			// Receive the data of sum value from NON-MASTER
			MPI_Recv(&data1[offset], &data2[offset], 1, MPI_DOUBLE, source_id, tag3, MPI_COMM_WORLD, &status);
		 }
		 
		 // Compute the final sum
		 offset = 0;
		 double final_sum = data1[offset];
		 offset = chunksize + leftover;
		 for (int i = 1; i < numtasks; i++) {
			final_sum = final_sum + data1[offset];
			offset = offset + chunksize;
		}
		
		printf("\n*** Parallel sum = %e\n\n", final_sum);		
    }
	
	// NON-MASTER tasks
	if (taskid > MASTER) {
		
		// Recieve portion of the array from the MASTER
		int source_id = MASTER;
		// Recieve offset value from MASTER
		MPI_Recv(&offset, 1, MPI_INT, source_id, tag1, MPI_COMM_WORLD, &status);
		// Receive data value from MASTER
		MPI_Recv(&data1[offset], &data2[offset], chunksize, MPI_DOUBLE, source_id, tag2, MPI_COMM_WORLD, &status);
		
		// Do summation for NON-MASTER
		double sum = compute_sum(offset, chunksize, taskid);
		
		// Send result back to the MASTER
		int dest_id = MASTER;
		// Send offset value to MASTER 
		MPI_Send(&offset, 1, MPI_INT, dest_id, tag1, MPI_COMM_WORLD);
		// Send the data of sum value to MASTER
		MPI_Send(&data1[offset], &data2[offset], 1, MPI_DOUBLE, dest_id, tag3, MPI_COMM_WORLD);
	}
	
	// Get final time and compute total elapsed time of parallel process
	double w2 = MPI_Wtime();
    double local_time = w2 - w1;
    double elapsed;
    MPI_Reduce(&local_time, &elapsed, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
	
	// MASTER task only
	if (taskid == MASTER) printf(">> Parallel time = %f seconds\n", (float)elapsed);
	
	// Finalize MPI environment
	MPI_Finalize();
	
	return 0;
}

double compute_sum(int offset, int chunksize, int taskid) {
	
	double sum = 0.0;
	double temp = 0.0;
	for (int i = offset; i < offset + chunksize; i++) {
		temp = data1[i] * data2[i];
		sum = sum + temp;
	}
	// Store the sum in data
	data1[offset] = sum;
	
	printf("Task %d sum = %e\n", taskid, sum);
	return sum;
}
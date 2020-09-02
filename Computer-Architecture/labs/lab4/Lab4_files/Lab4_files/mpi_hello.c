#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main(int argc, char *argv[]) {
	
	// Initialize MPI environment
	MPI_Init(&argc, &argv);
	
	// Get the number of tasks
	int numtasks;
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	
	// Get the task id
	int taskid;
	MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
	
	// Get the processor name for each task 
	char processor_name[MPI_MAX_PROCESSOR_NAME];
	int name_len;
	MPI_Get_processor_name(processor_name, &name_len);
	
	printf ("Hello from processor %s, task id %d out of %d tasks\n", 
	        processor_name, taskid, numtasks);
	
	// Finalize MPI environment
	MPI_Finalize();
}


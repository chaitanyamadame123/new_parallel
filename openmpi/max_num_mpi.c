#include"stdio.h"
#include"mpi.h"

int main (int argc,char **argv)
{
        int myid,size;
        int max_value = 0;
        
        MPI_Status status;
        MPI_Request request;
        //Initialize MPI Environment
        MPI_Init(&argc,&argv);

        //Get total number of processes 
        MPI_Comm_size(MPI_COMM_WORLD,&size);

        //Get my unique identification amoung all processes
        MPI_Comm_rank(MPI_COMM_WORLD,&myid);
        
        if (myid == 0) {
        	values = (int *)malloc(ARRAY_SIZE * sizeof(int));
        	srand((unsigned int)time(NULL));
        	printf("Random values: ");
        	for (int i = 0; i < ARRAY_SIZE; i++) {
            		values[i] = rand() % 100;
            		printf("%d ", values[i]);
        	}
        printf("\n");
    	}
	
	if (myid == 0) {
        	for (int i = 0; i < ARRAY_SIZE; i++) {
            		MPI_Send(&values[i], 1, MPI_INT, i % size, 0, MPI_COMM_WORLD);
        	}
    	}
    	
    	local_values = (int *)malloc((ARRAY_SIZE / size) * sizeof(int));
    	for (int i = 0; i < ARRAY_SIZE / size; i++) {
        	MPI_Recv(&local_values[i], 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    	}
    	
    	
    	int local_max = 0;
    	for (int i = 0; i < ARRAY_SIZE / size; i++) {
        	if (local_values[i] > local_max) {
            		local_max = local_values[i];
        	}
    	}
	
	
	MPI_Gather(&local_max, 1, MPI_INT, &max_value, 1, MPI_INT, 0, MPI_COMM_WORLD);
	
		
	if (rank == 0) {
        	for (int i = 0; i < size; i++) {
            		if (max_value < local_max[i]) {
                		max_value = local_max[i];
            		}
        	}
        	printf("Maximum value: %d\n", max_value);
    	}
	

        //End MPI environment
        MPI_Finalize();
        
        if(myid==0)
        {
        	printf("\nsum = %d\n",sum);
        }
      
}

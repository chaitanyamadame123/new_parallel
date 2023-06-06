#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>

#define n 900000000

int main(int argc, char **argv)
{
	int myid, size;
	int i, chunk;
        double step, result=0.0, start_t, end_t, exec_t;
        double x, pi, sum = 0.0;

        step = 1.0/(double)n;

	MPI_Status status;
	//Initialize MPI environment
	MPI_Init(&argc, &argv);
	
	//Get total number of processes
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	//Get my unique identification among all processes
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	
	chunk = n/size;
	
	
	if(myid==0){
	start_t = MPI_Wtime();
	}
	
	for(i=myid*chunk; i<(myid*chunk)+chunk; i++)
	{
		x = (i)*step;
		sum = sum + 4.0/(1.0+ x*x);
	}	
	
	pi = step*sum;
	
	MPI_Reduce(&pi, &result, 1,MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	
	if(myid==0){
	end_t = MPI_Wtime();
	exec_t = end_t - start_t;
	}
	
	if(myid==0)
	{
		printf("\n sum = %f\n",result);
		printf("\n Execution time = %f\n", exec_t);
	}
	
	
	//End MPI environment
	MPI_Finalize();
}

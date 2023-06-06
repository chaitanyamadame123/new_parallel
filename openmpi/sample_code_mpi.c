#include"stdio.h"
#include"mpi.h"

int main (int argc,char **argv)
{
	int myid,size;
	
	//Initialize MPI Environment
	MPI_Init(&argc,&argv);

	//Get total number of proccesses 
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	//get my unique identification amoung all processes
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);


	printf("HELLO World From %d out of %d.\n",myid,size);


	//End MPI environment
	MPI_Finalize();
}




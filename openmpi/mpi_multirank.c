#include"stdio.h"
#include"mpi.h"

int main (int argc,char **argv)
{
        int myid=0,size;
        int data_arr[2], data_arr2[2];
        int sum;
        MPI_Status status;
        MPI_Request request;
        //Initialize MPI Environment
        MPI_Init(&argc,&argv);

        //Get total number of processes 
        MPI_Comm_size(MPI_COMM_WORLD,&size);

        //Get my unique identification amoung all processes
        MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	
	if(myid==0)
	{
		sum = myid;
		
		MPI_Send(&sum,1,MPI_INT,myid+1,0,MPI_COMM_WORLD);
		MPI_Recv(&sum,1,MPI_INT,size-1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	}
	
	else if(myid==(size-1))
	{
		MPI_Recv(&sum,1,MPI_INT,myid-1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		sum = sum + myid;
		MPI_Send(&sum,1,MPI_INT,0,0,MPI_COMM_WORLD);
	}
	
	else
	{
		MPI_Recv(&sum,1,MPI_INT,myid-1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		sum = sum + myid;
		MPI_Send(&sum,1,MPI_INT,myid+1,0,MPI_COMM_WORLD);
	}
		
	
	

        //End MPI environment
        MPI_Finalize();
        
        if(myid==0)
        {
        	printf("\nsum = %d\n",sum);
        }
      
}

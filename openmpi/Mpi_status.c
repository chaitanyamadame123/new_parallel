#include"stdio.h"
#include"mpi.h"

int main (int argc,char **argv)
{
        int myid,size;
        int data_arr[2],data_arr2[2];
        
        MPI_Status status;
        //Initialize MPI Environment
        MPI_Init(&argc,&argv);

        //Get total number of processes 
        MPI_Comm_size(MPI_COMM_WORLD,&size);

        //Get my unique identification amoung all processes
        MPI_Comm_rank(MPI_COMM_WORLD,&myid);


       if(myid==0)
       {
       		data_arr[0]= 105;
       		data_arr[1]= 408;
       		data_arr2[0]=302;
		data_arr2[1]=201;
	
	printf("\nmyid: %d \t data_arr[0]=%d",myid,data_arr[0]);
	printf("\nmyid: %d \t data_arr[1]=%d",myid,data_arr[1]);
	
	MPI_Send(data_arr,2,MPI_INT,1,0,MPI_COMM_WORLD);
	printf("\nData sent.\n");
	
	MPI_Recv(data_arr2,2,MPI_INT,1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	printf("\nmyid: %d \t data_arr2[0]=%d",myid,data_arr2[0]);
	printf("\nmyid: %d \t data_arr2[1]=%d",myid,data_arr2[1]);
	
	
	
	
	
	
	printf("\nData Recived.\n");
	}
	if(myid==1) //process with id exactly equal to 1
	{
		data_arr[0]=10;
		data_arr[1]=20;
		data_arr2[0]=81;
		data_arr2[1]=108;
		
		MPI_Recv(data_arr,2,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		MPI_Send(data_arr2,2,MPI_INT,0,0,MPI_COMM_WORLD);
		
		printf("\nData Sent.");
		
		printf("\nmyid: %d \t data_arr2[0]=%d",myid,data_arr2[0]);
		printf("\nmyid: %d \t data_arr2[1]=%d",myid,data_arr2[1]);
		
		
		
		printf("\nData recived.");
		
		printf("\nmyid: %d \t data_arr[0]=%d",myid,data_arr[0]);
		printf("\nmyid: %d \t data_arr[1]=%d",myid,data_arr[1]);
		
		printf("\n\nProgram exit!\n");
		
		
	
	}

        //End MPI environment
        MPI_Finalize();
}

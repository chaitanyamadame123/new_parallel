#include"stdio.h"
#include"mpi.h"

int main (int argc,char **argv)
{
        int myid,size;
        int i,j;
        int value[10]={12,13,15,11,16,76,99,55,46,75};
        int max, val,recv_val; 
	MPI_Status status;
        //Initialize MPI Environment
        MPI_Init(&argc,&argv);

        //Get total number of processes 
        MPI_Comm_size(MPI_COMM_WORLD,&size);

        //Get my unique identification amoung all processes
        MPI_Comm_rank(MPI_COMM_WORLD,&myid);
        
        
        val = value[myid];
        for (i=size;i>0;i=i/2)
        {
        	j = i/2;
        	if (myid <i)
        	{
        		if (myid < j)
        		{
        			MPI_Recv(&recv_val,1,MPI_INT,myid+j,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        			if(val<recv_val)
        			{
        				val= recv_val;
        			}
        		}	
        		else
        		{
        			MPI_Send(&val,1,MPI_INT,myid-j,0,MPI_COMM_WORLD);
        		}
        	}	

	}
	
	if(myid==0)
	{
		for(i=1;i<size;i++)
		{
			MPI_Send(&val,1,MPI_INT,i,0,MPI_COMM_WORLD);
		}
		MPI_Recv(&recv_val,1,MPI_INT,MPI_ANY_SOURCE,10,MPI_COMM_WORLD,&status);
		printf("\n MAX value = %d and is available with myid = %d\n",val ,status.MPI_SOURCE);
	}
	else
	{
		MPI_Recv(&recv_val,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		if(recv_val == value[myid])
		{
			MPI_Send(&myid,1,MPI_INT,0,10,MPI_COMM_WORLD);
		}
	}	
		


        //End MPI environment
        MPI_Finalize();
        
       /* if(myid==0)
        {
        	printf("\n MAX value = %d and myid of max value = %d \n",val[0],val[1]);
        }*/
}

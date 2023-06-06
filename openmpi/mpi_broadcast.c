#include"stdio.h"
#include"mpi.h"

int main (int argc,char **argv)
{
        int myid,size;
        int sum;
        
        if(myid==0)
        {
        	sum = 100;
        }
        else
        {
        	sum =101;
        }
        //Initialize MPI Environment
        MPI_Init(&argc,&argv);

        //Get total number of processes 
        MPI_Comm_size(MPI_COMM_WORLD,&size);

        //Get my unique identification amoung all processes
        MPI_Comm_rank(MPI_COMM_WORLD,&myid);
        
        MPI_Bcast(&sum,1,MPI_INT,0,MPI_COMM_WORLD);
        
       
       
        printf("\n sum= %d of myid = %d\n",sum,myid);
        
        //End MPI environment
        MPI_Finalize();
        
        
}

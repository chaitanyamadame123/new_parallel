#include"stdio.h"
#include"mpi.h"

int main (int argc,char **argv)
{
        int myid,size;
        int sum;
        
        sum = 100;
        
        //Initialize MPI Environment
        MPI_Init(&argc,&argv);

        //Get total number of processes 
        MPI_Comm_size(MPI_COMM_WORLD,&size);

        //Get my unique identification amoung all processes
        MPI_Comm_rank(MPI_COMM_WORLD,&myid);
        
        MPI_Reduce(&myid ,&sum,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
        
        if(myid==0)
        {
        printf("\n sum= %d\n",sum);
        }
        //End MPI environment
        MPI_Finalize();
        
        
}

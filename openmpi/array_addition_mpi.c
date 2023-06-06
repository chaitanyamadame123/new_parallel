#include"stdio.h"
#include"mpi.h"
#include<stdlib.h>
#define ARRSIZE 20


int main (int argc,char **argv)
{
        int myid,size;
        int i;
        
        int a[ARRSIZE],b[ARRSIZE],c[ARRSIZE];
        
        int a_chunk[ARRSIZE/5];
        int b_chunk[ARRSIZE/5];
        int c_chunk[ARRSIZE/5];
        
        
        //Initialize MPI Environment
        MPI_Init(&argc,&argv);

        //Get total number of processes 
        MPI_Comm_size(MPI_COMM_WORLD,&size);

        //Get my unique identification amoung all processes
        MPI_Comm_rank(MPI_COMM_WORLD,&myid);
        
        if(size!=5)
        {
        	printf("\n Please use Exactly 5 Processes!\n");
        	MPI_Finalize();
        	exit(0);
        }
        
        
        if(myid==0)
        {
        	for(i=0;i<ARRSIZE;i++)
        	{
        		a[i]=i;
        		b[i]=i;
        		c[i]=0;
        	}
        	
        	printf("\nInitial data: ");
        	for(i=0;i<ARRSIZE;i++)
        	{
        		printf("\n%d\t%d\n",a[i],b[i]);
        		
        	}
        	
        }
        
        MPI_Scatter(a,ARRSIZE/5,MPI_INT,a_chunk,ARRSIZE/5,MPI_INT,0,MPI_COMM_WORLD);
        MPI_Scatter(b,ARRSIZE/5,MPI_INT,b_chunk,ARRSIZE/5,MPI_INT,0,MPI_COMM_WORLD);
      //Every process works on ARRSIZE/4 of data  
     for(i=0;i<ARRSIZE/5;i++)
     {
     	//Multiply received data by two
     		c_chunk[i] = a_chunk[i]+b_chunk[i];
     }
        //collect / Gather the data at root = 0
        MPI_Gather(c_chunk,ARRSIZE/5,MPI_INT,c,ARRSIZE/5,MPI_INT,0,MPI_COMM_WORLD);
        
        
        
        //If root
        if(myid==0)
        {
        	//print the data
        	printf("\nFinal data: ");
        	for(i=0;i<ARRSIZE;i++)
        	{
        		printf("\t%d",c[i]);
        	}
        	printf("\n\nProgram exit!\n");
        }
        
        //End MPI environment
        MPI_Finalize();
}

#include"stdio.h"
#include"mpi.h"

int main (int argc,char **argv)
{
        int myid,size,start,end,total_work_per_rank,chunksize;
	int a[10],b[10],c[10];
        //Initialize MPI Environment
        MPI_Init(&argc,&argv);

        //Get total number of processes 
        MPI_Comm_size(MPI_COMM_WORLD,&size);

        //Get my unique identification amoung all processes
        MPI_Comm_rank(MPI_COMM_WORLD,&myid);


        printf("HELLO World From %d out of %d.\n",myid,size);
        chunksize=2;
	total_work_per_rank = 10 / size;
	start = myid * chunksize;
	end  = myid * chunksize;
	
	for(int i=0;i<10;i++)
	{
		a[i] =i;
		b[i] =i;
		c[i] =0;
	}
	
	start = myid*chunksize;
	end= start + chunksize;
	
	
	for(;start<10;)
	for(int i=start;i<10;i+=chunksize*size)
	{
		for(int j=i;j<end;j++)
		{
			if( j<10){
				c[j]=a[j] + b[j];
				}
			else{
				break;
			     }
	}
	start=start + size*chunksize;
	end=start + chunksize;
	}
	for(int i=0;i<10;i++)
	{
		//start=id*total_work_per_rank;
		printf("c[i] = %d, a[i]=%d,b[i]=%d\n",c[i],a[i],b[i]);
	}

        //End MPI environment
        MPI_Finalize();
}

#include"stdio.h"
#include"mpi.h"

int main (int argc,char **argv)
{
        int myid,size,start,end,total_work_per_rank;
	int a[10],b[10],c[10];
        //Initialize MPI Environment
        MPI_Init(&argc,&argv);

        //Get total number of processes 
        MPI_Comm_size(MPI_COMM_WORLD,&size);

        //Get my unique identification amoung all processes
        MPI_Comm_rank(MPI_COMM_WORLD,&myid);


        printf("HELLO World From %d out of %d.\n",myid,size);
        
	total_work_per_rank = 10 / size;
	start = myid * total_work_per_rank;
	end  = myid * total_work_per_rank;
	
	for(int i=0;i<10;i+=size)
	{
		a[i] =i;
		b[i] =i;
		c[i] =0;
	}
	for
	
	for(int i=myid;i<10;i+=size)
	{
		c[i]=a[i] + b[i];
	}
	
	for(int i=0;i<10;i++)
	{
		//start=id*total_work_per_rank;
		printf("c[i] = %d, a[i]=%d,b[i]=%d\n",c[i],a[i],b[i]);
	}

        //End MPI environment
        MPI_Finalize();
}

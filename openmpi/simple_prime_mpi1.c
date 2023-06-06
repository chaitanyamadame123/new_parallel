#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<mpi.h>


#define N 100000
/*
                N  PRIME_NUMBER

                1           0
               10           4
              100          25
            1,000         168
           10,000       1,229
          100,000       9,592
        1,000,000      78,498
       10,000,000     664,579
      100,000,000   5,761,455
    1,000,000,000  50,847,534

*/
int main(int argc, char **argv)
{
	int myid, size;
	int i, j, chunck;
	int count, flag, result = 0;
	double exe_time, start_t, end_t, exec_t;

	
	count = 0; // 2 is prime. Our loop starts from 3
	

	MPI_Init(&argc, &argv);
	
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	MPI_Comm_rank(MPI_COMM_WORLD, &myid);

	chunck = N/size;
	
	start_t = MPI_Wtime();

	for(i=myid; i<N; i+=size)
	{
		if(i>2)
		{
		 	flag = 0;
			for(j=2;j<i;j++)	
		    	{
			    if((i%j) == 0)
			    {
				    flag = 1;
				    break;
			    }
		    	}
		
       		if(flag == 0)
        	{
        		count++;

        	}
		}
	}

	MPI_Reduce(&count, &result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	
	if(myid==0){
	end_t = MPI_Wtime();
	exec_t = end_t - start_t;
	}
	
	if(myid==0)
	{
		printf("\nNumber of primes = %d\n",result+1);
		printf("\nExecution time = %f\n", exec_t);
	}
	
	
	//End MPI environment
	MPI_Finalize();	

}


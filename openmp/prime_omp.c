#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<omp.h>

#define N 1000000
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
int main()
{
	int i, j;
	int count, flag;
	double exe_time, start, end;

	count = 1; // 2 is prime. Our loop starts from 3
	
        start = omp_get_wtime();
	
	#pragma omp parallel for private(i, j, flag) reduction(+:count) num_threads(5)
	for(i=0;i<N;i++)
	{
		if(i>2)
		{
		 	flag = 0;
			for(j=2;j<i;j++)	
		    {
			    if((i%j) == 0)
			    {
				    flag = 1;
			//	    break;
			    }
		    }
		if(flag == 0)
		{
			count++;
		}
		}
	}
	
        end = omp_get_wtime();
	
        printf("Time Required %f\n", end-start);
        printf("Number of primes: %d.\n", count);
        return 0;
	
}


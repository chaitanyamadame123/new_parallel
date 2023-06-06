#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <mpi.h>
#define N 1000000000
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
    int i, j;
    int count = 1;
    double exe_time;
    struct timeval stop_time, start_time;
    int rank, size;
    int local_count = 0;
    int start, end;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    int chunk_size = N / size;
    int remainder = N % size;
    start = rank * chunk_size + 2;
    end = start + chunk_size - 1;
    if (rank == size - 1) 
    {
        end += remainder;
    }
    gettimeofday(&start_time, NULL);
    for (i = start; i <= end; i++) 
    {
        int flag = 0;
        for (j = 2; j < i; j++) 
        {
            if (i % j == 0) 
            {
                flag = 1;
                break;
            }
        }
        if (flag == 0) 
        {
            local_count++;
        }
    }
    MPI_Reduce(&local_count, &count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    gettimeofday(&stop_time, NULL);
    exe_time = (stop_time.tv_sec + (stop_time.tv_usec / 1000000.0)) - (start_time.tv_sec + (start_time.tv_usec / 1000000.0));
    if (rank == 0) 
    {
        printf("\n Number of prime numbers = %d \n Execution time is = %lf seconds\n", count, exe_time);
    }
    MPI_Finalize();
    return 0;
}

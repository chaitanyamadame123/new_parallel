#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

#define N 1000000

int is_prime(int num) {
    if (num < 2)
        return 0;
    
    for (int i = 2; i <= sqrt(num); i++) {
        if (num % i == 0)
            return 0;
    }
    
    return 1;
}

int main(int argc, char** argv) {
    int rank, size;
    int local_count = 0;
    int global_count = 0;
    double exe_time;
    double start_time, stop_time;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    int chunk_size = N / size;
    int start = rank * chunk_size + 2;
    int end = (rank == size - 1) ? N : (rank + 1) * chunk_size;
    
    start_time = MPI_Wtime();
    
    for (int i = start; i <= end; i++) {
        if (is_prime(i))
            local_count++;
    }
    
    MPI_Reduce(&local_count, &global_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    
    stop_time = MPI_Wtime();
    exe_time = stop_time - start_time;
    
    if (rank == 0) {
        printf("\n Number of prime numbers = %d \n Execution time = %lf seconds\n", global_count, exe_time);
    }
    
    MPI_Finalize();
    return 0;
}

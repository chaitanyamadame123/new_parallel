#include <stdio.h>
#include <mpi.h>

#define ARRAY_SIZE 10

int main(int argc, char **argv) {
    int myid, size;
    int a[ARRAY_SIZE], b[ARRAY_SIZE], c[ARRAY_SIZE];
    int chunksize = 2;
    // Initialize MPI Environment
    MPI_Init(&argc, &argv);

    // Get total number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Get my unique identification among all processes
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    printf("Hello World From %d out of %d.\n", myid, size);

    // Calculate the workload division
    int total_work = ARRAY_SIZE;
    int total_work_per_rank = total_work / size;
    int start = myid * chunksize ;
    int end = start + chunksize ;

    // Assign values to arrays a and b
    for (int i = start; i < end; i++) {
        a[i] = i;
        b[i] = i;
        c[i] = 0;
    }

    // Perform addition of arrays a and b
    for (int i = start; i < end; i++) {
        c[i] = a[i] + b[i];
    }

    // Print results on the root process
     
        for (int i = 0; i < total_work; i++) {
            printf("c[%d] = %d, a[%d] = %d, b[%d] = %d\n", i, c[i], i, a[i], i, b[i]);
        }
    

    // End MPI environment
    MPI_Finalize();
    return 0;
}

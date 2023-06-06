#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size;
    int numbers[] = {10, 20,125, 58, 55, 94, 26, 63, 75, 73, 15};
    int num_count = sizeof(numbers) / sizeof(int);

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int local_max = 0;
    int i;
    for (i = rank; i < num_count; i += size) {
        if (numbers[i] > local_max) {
            local_max = numbers[i];
        }
    }

    int global_max;
    if (rank != 0) {
        MPI_Send(&local_max, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    } else {
        global_max = local_max;
        for (i = 1; i < size; i++) {
            int received_max;
            MPI_Recv(&received_max, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            if (received_max > global_max) {
                global_max = received_max;
            }
        }
    }

    if (rank == 0) {
        printf("The maximum number is: %d\n", global_max);
    }

    MPI_Finalize();
    return 0;
}

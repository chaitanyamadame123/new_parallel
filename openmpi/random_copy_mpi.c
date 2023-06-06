#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define ARRAY_SIZE 10

int main(int argc, char** argv) {
    int rank, size;
    int max_value = 0;
    int *values = NULL;
    int *local_values = NULL;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Only the root process generates random values
    if (rank == 0) {
        values = (int *)malloc(ARRAY_SIZE * sizeof(int));
        srand((unsigned int)time(NULL));
        printf("Random values: ");
        for (int i = 0; i < ARRAY_SIZE; i++) {
            values[i] = rand() % 100;
            printf("%d ", values[i]);
        }
        printf("\n");
    }

    // Broadcast the values array element-wise to all processes
    if (rank == 0) {
        for (int i = 0; i < ARRAY_SIZE; i++) {
            MPI_Send(&values[i], 1, MPI_INT, i % size, 0, MPI_COMM_WORLD);
        }
    }

    // Each process receives its portion of the values array
    local_values = (int *)malloc((ARRAY_SIZE / size) * sizeof(int));
    for (int i = 0; i < ARRAY_SIZE / size; i++) {
        MPI_Recv(&local_values[i], 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    // Each process finds the maximum value in its portion of the array
    int local_max = 0;
    for (int i = 0; i < ARRAY_SIZE / size; i++) {
        if (local_values[i] > local_max) {
            local_max = local_values[i];
        }
    }

    // Gather the local maximums to the root process
    MPI_Gather(&local_max, 1, MPI_INT, &max_value, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Only the root process finds the overall maximum value
    if (rank == 0) {
        for (int i = 0; i < size; i++) {
            if (max_value < local_max[i]) {
                max_value = local_max[i];
            }
        }
        printf("Maximum value: %d\n", max_value);
    }

    // Clean up
    if (rank == 0) {
        free(values);
    }
    free(local_values);
    MPI_Finalize();

    return 0;
}


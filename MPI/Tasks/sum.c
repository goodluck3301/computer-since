#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    int num_procs, rank, arr_size = 1000, sum = 0, local_sum = 0;
    int *arr = (int*) malloc(sizeof(int) * arr_size);
    srand(time(NULL));

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int chunk_size = arr_size / num_procs;
    int *local_arr = (int*) malloc(sizeof(int) * chunk_size);

    if (rank == 0) {
        for (int i = 0; i < arr_size; i++) {
            arr[i] = rand() % 100;
        }
    }

    MPI_Scatter(arr, chunk_size, MPI_INT, local_arr, chunk_size, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < chunk_size; i++) {
        local_sum += local_arr[i];
    }

    MPI_Reduce(&local_sum, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Sum of array elements: %d\n", sum);
    }

    MPI_Finalize();
    free(arr);
    free(local_arr);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void bubble_sort(int *arr, int size) {
    int temp, i, j;
    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main(int argc, char **argv) {
    int rank, size;
    int *data, *local_data, *sorted_data;
    int local_size, i;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    local_size = 50000 / size;
    local_data = (int*) malloc(local_size * sizeof(int));
    sorted_data = (int*) malloc(50000 * sizeof(int));

    if (rank == 0) {
        data = (int*) malloc(50000 * sizeof(int));
        for (i = 0; i < 50000; i++) {
            data[i] = rand() % 100;
        }
    } else {
        data = NULL;
    }

    MPI_Scatter(data, local_size, MPI_INT, local_data, local_size, MPI_INT, 0, MPI_COMM_WORLD);

    bubble_sort(local_data, local_size);

    MPI_Gather(local_data, local_size, MPI_INT, sorted_data, local_size, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        bubble_sort(sorted_data, 50000);
        for (i = 0; i < 50000; i++) {
            printf("%d ", sorted_data[i]);
        }
        printf("\n");
        free(data);
    }

    free(local_data);
    free(sorted_data);

    MPI_Finalize();
    return 0;
}

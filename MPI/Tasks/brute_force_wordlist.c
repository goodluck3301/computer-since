#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

#define MAX_STRING_LENGTH 4

int count = 0;

char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
int charset_length = sizeof(charset) - 1;

void generate_strings(char* string, int length, int depth, int rank, int size) {
    if (depth == length) {
        printf("Rank %d: %s\n", rank, string);
        count = count+1;
        return;
    }
    for (int i = rank; i < charset_length; i += size) {
        string[depth] = charset[i];
        generate_strings(string, length, depth + 1, rank, size);
    }
}

int main(int argc, char** argv) {
    int rank, size;
    char string[MAX_STRING_LENGTH+1] = {0};
    double start_time, end_time, elapsed;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    start_time = MPI_Wtime();
    
    generate_strings(string, MAX_STRING_LENGTH, 0, rank, size);

    end_time = MPI_Wtime();

    elapsed = end_time - start_time;

    printf("\n---------------------\n");
    printf("Count - %d \n",count);
    printf("Total time: %f seconds\n", elapsed);
    printf("---------------------\n");

    MPI_Finalize();
    return 0;
}

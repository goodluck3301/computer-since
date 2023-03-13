#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHARACTERS "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
int count = 0;

int main(int argc, char** argv) {
    double start_time, end_time, time;
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int i, j, k, l, m, n, o, p;
    char password[9];

    start_time = MPI_Wtime();

    for (i = rank; i < strlen(CHARACTERS); i += size) {
        password[0] = CHARACTERS[i];
        for (j = 0; j < strlen(CHARACTERS); j++) {
            password[1] = CHARACTERS[j];
            for (k = 0; k < strlen(CHARACTERS); k++) {
                password[2] = CHARACTERS[k];
                for (l = 0; l < strlen(CHARACTERS); l++) {
                    password[3] = CHARACTERS[l];
                    for (m = 0; m < strlen(CHARACTERS); m++) {
                        password[4] = CHARACTERS[m];
                        for (n = 0; n < strlen(CHARACTERS); n++) {
                            password[5] = CHARACTERS[n];
                            for (o = 0; o < strlen(CHARACTERS); o++) {
                                password[6] = CHARACTERS[o];
                                for (p = 0; p < strlen(CHARACTERS); p++) {
                                    password[7] = CHARACTERS[p];
                                    count++;
                                    printf("\nRank [%d] - ", rank);
                                    printf("%s", password);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    end_time = MPI_Wtime();
    time = end_time - start_time;

    printf("\n---------------------\n");
    printf("Count - %d \n",count);
    printf("Total time: %f seconds\n", time);
    printf("---------------------\n");

    MPI_Finalize();
    return 0;
}


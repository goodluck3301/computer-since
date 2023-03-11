#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int n_coupons = 5000;
    int n_draws = 100000;

    int n_subtasks = size - 1;


    if (rank == 0) {
        double start_time = MPI_Wtime();
        

        double total_draws = 0;
        for (int i = 1; i < size; i++) {
            double sub_draws;
            MPI_Recv(&sub_draws, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            total_draws += sub_draws;
        }

  
        double avg_draws = total_draws / (n_coupons * n_subtasks);
        printf("Average number of draws: %f\n", avg_draws);

        double end_time = MPI_Wtime();
        printf("Elapsed time: %f seconds\n", end_time - start_time);
    }

    else {
        srand(time(NULL) + rank);

        int collected[n_coupons];
        for (int i = 0; i < n_coupons; i++) {
            collected[i] = 0;
        }

        int num_collected = 0;
        int num_draws = 0;
        while (num_collected < n_coupons) {
            int coupon = rand() % n_coupons;
            if (!collected[coupon]) {
                collected[coupon] = 1;
                num_collected++;
            }
            num_draws++;
        }
      
        double sub_draws = (double)num_draws;
        MPI_Send(&sub_draws, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}

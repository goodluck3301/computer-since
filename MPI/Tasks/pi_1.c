#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>
#define NUMRECT 10000000

int main(int argc, char **argv) {

    int        numRect;                                    
    int        i;
    int        rank, size;               
    double        width;                            
    double        startingX = -1.0, overallWidth = 2.0;
    double        x;                                       
    double        pi, halfPi, partPi = 0.0;  


    numRect = argc == 2 ? atoi(argv[1]) : NUMRECT;        


    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);


    numRect        /= size;                    
    overallWidth        /= size;               
    startingX        += rank * overallWidth;   


    width        = overallWidth / numRect;     
    x = startingX - width/2;                   


    for (i=0; i<numRect; ++i) {                
            x         += width;
            partPi += width * sqrt(1.0 - x*x);
    }


    MPI_Reduce(&partPi, &halfPi, 1, MPI_DOUBLE,  MPI_SUM, 0, MPI_COMM_WORLD);


    if (rank == 0) {
            pi = 2.0 * halfPi;
            printf ("\n==\n==\t%20s = %15.10f\n",    "pi",        pi);
            printf ("==\t%20s = %15d\n",       "total rectangles",    size*numRect);
            printf ("==\t%20s = %15d\n==\n\n",    "processes",          size);
    }
    MPI_Finalize();
    return 0;
}

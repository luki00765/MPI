#include<stdio.h>
#include<mpi.h>

int main(int argc, char **argv){

	int rank, size;
	int dane = 0;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if( rank == 0 ){
	    dane = 25;
	    printf("rank%i: Wysylam dane=%i, do pozostalych procesow\n", rank, dane);
	}
	
	MPI_Bcast(&dane, 1, MPI_INT, 0, MPI_COMM_WORLD);
	if( !rank == 0 ){	
	printf("rank%i: Odebralem dane: %i\n", rank, dane);
	}

	MPI_Finalize();
	return 0;
}

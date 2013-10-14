
#include <stdio.h>
#include <mpi.h>

int main( int argc, char **argv ){

	int rank; /* zwraca numer danego procesu "losowo" */
	int size; /* zwraca długość procesów */

	char magic_number[7] = "bolek";
	char magic_number2[7] = "lubie";
	char odebrane[7];
	MPI_Status statusik; /* funkcja która pokazuje od jakiego procesu została dostarczona wiadomość */

	MPI_Init(&argc,&argv);

	MPI_Comm_size( MPI_COMM_WORLD , &size );
	MPI_Comm_rank( MPI_COMM_WORLD , &rank );
	fflush(stdout);
	if( rank == 0 ){
		snprintf(magic_number, 100, "lolek");
		snprintf(magic_number2, 100, "placki");
		printf("rank%i: wysylam %s do procesu %i\n",rank,magic_number,1);
		printf("rank%i: wysylam %s do procesu %i\n",rank,magic_number2,2);
/*void *buf, int count, MPI_Datatype datatype, int dest,int tag, MPI_Comm comm*/
	MPI_Send( magic_number, 5, MPI_CHARACTER, 1, 777, MPI_COMM_WORLD );

	MPI_Send( magic_number2, 7, MPI_CHARACTER, 2, 777, MPI_COMM_WORLD);
	}
	if( rank == 1 ){
		printf("rank%i: magic_number = %s\n",rank,magic_number);
/*(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status)*/
	MPI_Recv(odebrane, 5, MPI_CHARACTER, 0, 777, MPI_COMM_WORLD, &statusik);
		printf("rank%i: magic_number = %s (po odbiorze), size = %d\n",rank,odebrane,size);
	}
	if( rank == 2 ){
	printf("rank%i: magic_number2 = %s\n", rank, magic_number2);
	MPI_Recv(odebrane, 7, MPI_CHARACTER, 0, 777, MPI_COMM_WORLD, &statusik);
	printf("rank%i: magic_number = %s (po odbiorze), size = %d\n",rank, odebrane,size);
	}	
	printf("rank%i: moj numer: %i\n",rank,rank);

	MPI_Finalize();
	return 0;
}


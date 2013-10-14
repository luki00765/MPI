
#include <stdio.h>
#include <mpi.h>

int main( int argc, char **argv ){

	int rank;
	int size;

	int magic_number = 123;
	int odebrane;
	MPI_Status statusik;

	MPI_Init(&argc,&argv);

	MPI_Comm_size( MPI_COMM_WORLD , &size );
	MPI_Comm_rank( MPI_COMM_WORLD , &rank );

	if( rank == 0 ){
		//magic_number = 666;		
		printf("rank%i: Send %i to Rank%i\n",rank,magic_number,1);
		MPI_Send( &magic_number, 1, MPI_INT, 1, 777, MPI_COMM_WORLD );
MPI_Recv(&odebrane, 1, MPI_INT, 3, 777, MPI_COMM_WORLD, &statusik); 
magic_number = odebrane;	
printf("rank%i: Get magic_number: %i, from rank%i\n",rank,magic_number,3);
	}
	if( rank == 1 ){
		//printf("rank%i: magic_number = %i\n",rank,magic_number);
		MPI_Recv(&odebrane, 1, MPI_INT, 0, 777, MPI_COMM_WORLD, &statusik);
		printf("rank%i: magic_number = %i RECIVE from rank%i\n",rank,odebrane,0);
		printf("rank%i: Send %i to Rank%i\n",rank,magic_number,2);
/*(void *buf, int count, MPI_Datatype datatype, int dest,int tag, MPI_Comm comm)*/		
		MPI_Send( &magic_number, 1, MPI_INT, 2, 777, MPI_COMM_WORLD );
	}
	if( rank == 2 ){
/*(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status)*/
		MPI_Recv( &odebrane, 1, MPI_INT, 1, 777, MPI_COMM_WORLD, &statusik);
		printf("rank%i: magic_number: %i RECIVE from rank%i\n",rank, odebrane, 1);
		printf("rank%i: Send %i to Rank%i\n",rank,magic_number,3);
		MPI_Send( &magic_number, 1, MPI_INT, 3, 777, MPI_COMM_WORLD );
	}
	if( rank == 3 ){
		MPI_Recv( &odebrane, 1, MPI_INT, 2, 777, MPI_COMM_WORLD, &statusik);
		printf("rank%i: magic_number: %i RECIVE from rank%i\n",rank,odebrane, 2);
		magic_number = 997;
		printf("magic_number: %i, SEND to rank%i\n", magic_number,0);
		MPI_Send( &magic_number, 1, MPI_INT, 0, 777, MPI_COMM_WORLD );
	}

	MPI_Finalize();
	return 0;
}


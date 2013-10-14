/* networld.c */
#include <stdio.h>
#include "mpi.h"

int main(int argc, char **argv) {
  int rank;
  char host[150];
  int namelen;

  /* Message tag */
  int tag = 1;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Get_processor_name(host,&namelen);

  printf("Hello world (Rank: %d / Host: %s)\n", rank, host);
  fflush(stdout);
  if (rank == 0) {
      int numprocs, x;
      char msg[50];
      MPI_Status status;

      MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
      for (x = 1; x < numprocs; x++) {
        MPI_Recv(msg, 50, MPI_CHARACTER, MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, &status);
        printf("Msg from %d: '%s'\n", status.MPI_SOURCE, msg);
        fflush(stdout);
      }
  } else {
      char msg[50];

      snprintf(msg, 50, "Hello from node rank %d.", rank);
      MPI_Send(msg, 50, MPI_CHARACTER, 0, tag, MPI_COMM_WORLD);
  }

  MPI_Finalize();
  return 0;
}

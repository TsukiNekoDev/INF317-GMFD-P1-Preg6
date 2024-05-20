#include "math.h"
#include "stdio.h"
#include "mpi.h"

int main(int argc, char *argv[])
{
int procesador, nprocesadores, i;

//int N = 1000000;
//int d = N/3;
int ia = 0, fa = 333332;
int ib = 333333, fb = 666665;
int ic = 666666, fc = 1000000;
int v1[N], v2[N], v3[N];

MPI_Init(&argc, &argv);

MPI_Comm_rank(MPI_COMM_WORLD, &procesador); //rank
MPI_Comm_size(MPI_COMM_WORLD, &nprocesadores); //size

if (procesador==0)
{
  MPI_Recv(v1,N,MPI_INT,1,0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  MPI_Recv(v2,N,MPI_INT,2,0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  MPI_Recv(v3,N,MPI_INT,3,0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  int s = 0;
  for (i=ia;i<fa;i++) 
  	s += v1[i];
  for (i=ib;i<fb;i++) 
  	s += v2[i];
  for (i=ic;i<fc;i++) 
  	s += v3[i];
  
  int pi = sqrt(s*6);
  printf("pi= %d \n", pi);
  
}
if (procesador==1)
{
  for(i=ia;i<fa;i++)
 	v1[i]=1/(i*i);
  MPI_Send(v1,N,MPI_INT,0,0,MPI_COMM_WORLD);
}
if (procesador==2)
{
  for(i=ib;i<fb;i++)
 	v2[i]=1/(i*i);
  MPI_Send(v2,N,MPI_INT,0,0,MPI_COMM_WORLD);
}

if (procesador==3)
{
  for(i=ic;i<fc;i++)
 	v3[i]=1/(i*i);
  MPI_Send(v3,N,MPI_INT,0,0,MPI_COMM_WORLD);
}

MPI_Finalize();
}


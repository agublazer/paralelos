#include <mpi.h>
#include <stdio.h>
void other_work(int myid);
float suma();

int main(int argc, char* argv[])
{
      int p, myid, tag, master, proc;
      float i_sum, my_int;
      MPI_Comm comm;
      MPI_Request request;
      MPI_Status status;

      comm = MPI_COMM_WORLD;       
      MPI_Init(&argc,&argv);
      MPI_Comm_rank(comm, &myid);
      MPI_Comm_size(comm, &p);

      master = 0;
      tag = 123;        /* set the tag to identify this particular job */
      my_int = suma();

      printf("Process %d has the partial result of %f \n", myid, my_int);

      if(myid == master) //proceso que recupera toda la info y la suma
      {
        i_sum = my_int;
        for (proc=1;proc<p;proc++) {
          MPI_Recv(  
                &my_int, 1, MPI_FLOAT,    /* triplet of buffer, size, data type */
                MPI_ANY_SOURCE,           /* message source */
                MPI_ANY_TAG,              /* message tag */
                comm, &status);           /* status identifies source, tag */
          i_sum += my_int;
        }
        printf("Suma total = %f \n",i_sum); /* sum of my_int */
      }
      else 
      {
        MPI_Isend(                         /* non-blocking send */
              &my_int, 1, MPI_FLOAT,       /* triplet of buffer, size, data type */
              master, 
              tag, 
              comm, &request);             /* send my_int to master */
        other_work(myid);
        MPI_Wait(&request, &status);       /* block until Isend is done */
      }
      MPI_Finalize();                      /* let MPI finish up ... */
}
void other_work(int myid)
{
  printf("more work on process %d \n", myid);
}

float suma()
{
      int j;
      //printf("INIT SUMA \n");
      float integ = 0.0;                 /* initialize */
      for (j= 0 ;j < 100 ;j++) {          /* sum integrals */
        integ += 1.0;
      }
      //printf("FIN SUMA \n");
      return integ;
}

#include <sys/sysinfo.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#define BILLION  1E9; 
#define n 50000
#define m 50000

long long thread_count = 0;
long long A[n][m];
long long x[m];
long long y[m];

void print_mat()
{
    printf("MAT: \n");
    for(int a = 0; a<n;a++)
    {
        for(int b = 0;b<m;b++)
            printf("%lld ",A[a][b]);
        printf("\n");
    }
    printf("X: \n");
    for(int b = 0;b<m;b++)
        printf("%lld ",x[b]);
    printf("\n");
}

void print_result()
{
    printf("Y: \n");
    for(int b = 0;b<m;b++)
        printf("%lld ",y[b]);
    printf("\n");

}

void print_processor_count()
{
    printf("This system has %d processors configured and "
        "%d processors available.\n",
        get_nprocs_conf(), get_nprocs());
}


void *Pth_mat_vect(void *rank)
{
    long my_rank = (long) rank;
    int i,j;
    int local_m = m/thread_count;
    int my_first_row = my_rank*local_m;
    int my_last_row = (my_rank+1)*local_m -1;
    for(i = my_first_row; i<=my_last_row;i++)
    {
        y[i] = 0.0;
        for(j = 0; j<n; j++)
            y[i]+=A[i][j]*x[j];
    }

    return NULL;
}
int main() 
{
    for(int a = 0; a<n; a++)
    {
        for(int b = 0; b<m;b++)
            A[a][b] = rand()%5000+1;
    }
    for(int a = 0; a<m;a++)
    {
        x[a] = rand()%5000+1;
    }
    print_processor_count();
    //print_mat();
    //print_result();
    scanf("%lld",&thread_count);
    pthread_t threads[thread_count];
    long t;
    struct timespec requestStart, requestEnd;
    clock_gettime(CLOCK_REALTIME, &requestStart);
    for(t=0; t<thread_count; t++)
    {
        pthread_create(&threads[t], NULL, Pth_mat_vect, t);
    }

    for(t=0;t<thread_count;t++)
    {
        pthread_join(threads[t], NULL);   
    }
    //print_result();
    clock_gettime(CLOCK_REALTIME, &requestEnd);
     // Calculate time it took
    double accum = ( requestEnd.tv_sec - requestStart.tv_sec )
       + ( requestEnd.tv_nsec - requestStart.tv_nsec )
       / BILLION;
    printf( "Time taken: %lf\n", accum );
    return 0;
}

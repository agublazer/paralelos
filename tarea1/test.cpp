#include<iostream>
#include<chrono>
#include<stdlib.h>
#include<time.h>
using namespace std;

int main()
{
    using namespace std::chrono;
    int MAX = 700,i,j;
    int A[MAX][MAX], x[MAX], y[MAX];
    srand(time(NULL));
    for(i = 0;i<MAX;i++){
        for(j=0;j<MAX;j++)
            A[i][j] = 0;
    }

    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    for(int i = 0; i<MAX; i++){
        for(int j = 0; j<MAX; j++)
            y[i] += A[i][j]*x[j];
    }
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
    std::cout << "for loop #1: " << time_span.count() << " seconds.";
    std::cout << std::endl;

    high_resolution_clock::time_point t3 = high_resolution_clock::now();
    for(int j = 0; j<MAX; j++){
        for(int i = 0; i<MAX; i++)
            y[i] += A[i][j]*x[j];
    }
    high_resolution_clock::time_point t4 = high_resolution_clock::now();
    duration<double> time_span2 = duration_cast<duration<double>>(t4 - t3);
    std::cout << "for loop #2: " << time_span2.count() << " seconds.";
    std::cout << std::endl;

}

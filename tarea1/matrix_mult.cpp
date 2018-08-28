#include<iostream>
#include <math.h>

using namespace std;

const int n = 4;


void display(int C[n][n], int r1, int c2)
{
	int i, j;
	cout<<"-------------------------------"<<endl;
	for(i = 0; i < r1; ++i)
	{
		for(j = 0; j < c2; ++j)
			cout << C[i][j] << " ";
		cout<<endl;
	}
	cout<<"-------------------------------"<<endl;
}

void blocked_multiply(int a[n][n], int b[n][n], int c[n][n])
{
	int step_b = 3;
	for(int i0 = 0;i0<n;i0+=step_b)
	{
		for(int j0 = 0; j0<n; j0+=step_b)
		{
			for(int k0 = 0; k0<n;k0+=step_b)
			{
				for(int i = i0;i < min(i0+step_b,n);i++)
				{
					for(int j = j0; j < min(j0+step_b,n);j++)
					{
						for(int k = k0; k< min(k0+step_b,n);k++)
						{
							c[i][j] = c[i][j] + a[i][k]*b[k][j];
							display(c,n,n); 

						}
					}
				}
			}
		}
	}
}
void multiply(int A[n][n], int B[n][n], int C[n][n], int r1, int c1, int r2, int c2)
{
	int i, j, k;

	for(i = 0; i < r1; ++i)
	{
		for(j = 0; j < c2; ++j)
		{
			C[i][j] = 0;
		}
	}

	for(i = 0; i < r1; ++i)
	{
		for(j = 0; j < c2; ++j)
		{
			for(k=0; k<c1; ++k)
			{
				C[i][j] += A[i][k] * B[k][j];
				display(C,n,n);
			}
		}
	}
}

int main()
{
	
	int a[n][n] = {{2,2,2,2},
					{2,2,2,2},
					{2,2,2,2},
					{2,2,2,2}};

	int b[n][n] = {{2,2,2,2},
					{2,2,2,2},
					{2,2,2,2},
					{2,2,2,2}};
    int c[n][n] = {{0,0,0,0},
					{0,0,0,0},
					{0,0,0,0},
					{0,0,0,0}};

    //blocked_multiply(a,b,c);
    multiply(a,b,c,n,n,n,n);
    //display(c,n,n);

}

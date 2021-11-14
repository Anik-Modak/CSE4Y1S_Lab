#include <bits/stdc++.h>
#include <mpi.h>
using namespace std;

int main(int argc, char** argv)
{
    int rank, size;
    MPI_Status status;
	MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    double t1, t2;
    if(rank==0)
        t1 = MPI_Wtime();

    int n = 10;
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int local_n = n / size;
    int local_arr[local_n], sum[size];

    MPI_Scatter(arr, local_n, MPI_INT, local_arr, local_n, MPI_INT, 0, MPI_COMM_WORLD);

    int local_sum = 0;
    for (int j = 0; j < local_n; j++)
    {
        local_sum += local_arr[j];
    }
    printf("Rank %d: local sum: %d\n", rank, local_sum);

    MPI_Gather(&local_sum, 1, MPI_INT, sum, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if(rank==0)
    {
        int global_sum = 0;
        for(int i=0; i<size; i++)
            global_sum += sum[i];

        cout<<"Total sum: "<<global_sum<<endl;

        t2 = MPI_Wtime();
        printf( "Elapsed time is %f\n", t2 - t1 );
    }
    MPI_Finalize();
    return 0;
}
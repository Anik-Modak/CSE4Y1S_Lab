#include <bits/stdc++.h>
#define MX 10005
#include <mpi.h>
using namespace std;

int main(void)
{
    int comm_sz, rank;
    MPI_Status status;
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    char greeting[MX];
    if (rank != 0)
    {
        sprintf(greeting, "Anik Modak");
        cout << "Sending from rank " << rank << endl;
        MPI_Send(greeting, strlen(greeting)+1, MPI_CHAR, 0, 0,MPI_COMM_WORLD);
    }
    else
    {
        printf("Receiving from rank %d: ", rank);
        for (int i = 1; i < comm_sz; i++)
        {
            MPI_Recv(greeting, MX, MPI_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("%s\n", greeting);
        }
    }
    MPI_Finalize();
    return 0;
}
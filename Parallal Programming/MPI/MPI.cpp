#include<bits/stdc++.h>
#include <mpi.h>

using namespace std;

const int MAX_STRING = 100;

int main(void)
{
    puts("t-0");
    char greeting[MAX_STRING];
    int comm_sz;
    int my_rank;
    puts("t-1");
    MPI_Init(NULL, NULL);
    puts("t-2");
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    //cout<<my_rank<<" "<<comm_sz<<endl;

    if (my_rank != 0)
    {
        sprintf(greeting, "Anik Modak");
        cout<<"Sending from : "<<my_rank<<endl;
        MPI_Send(greeting, strlen(greeting)+1, MPI_CHAR, 0, 0,MPI_COMM_WORLD);
    }
    else
    {
        printf("Greetings from process %d of %d!_\n", my_rank, comm_sz);

        for (int q = 1; q < comm_sz; q++)
        {
            MPI_Recv(greeting, MAX_STRING, MPI_CHAR, q,0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("%s\n", greeting);
        }
        puts("end - else");
    }

    cout<<"end of -----> "<<my_rank<<endl;

    //cout<<MPI_COMM_WORLD<<endl;

    MPI_Finalize();
    return 0;
}

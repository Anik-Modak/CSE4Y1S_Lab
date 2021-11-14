#include<bits/stdc++.h>
#include<mpi.h>
using namespace std;


double func(double x)
{
    return x*x;
}

double trapizoid(double a, double b, int trap_count, double height)
{

    double segment_area,tmp;
    int i;
    /*calculating area of trapizoid of two end point*/
    // cout<<"start - ";
    segment_area = (func(a) + func(b))/2.0;
    for(i=1; i < trap_count; i++)
    {
        segment_area += func(a + i*height);
    }
    segment_area *= height;
    //cout<<"end"<<endl;
    return segment_area;
}


int main()
{
    int my_rank, comm_sz, n, local_n;
    double a, b, height, local_a, local_b,total_area,local_area;
    int source;

    MPI_Init(NULL,NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    //input then bcast the data to all process
    if(my_rank==0)
    {
        puts("Input number of process, starting point, ending point :");
        scanf("%d %lf %lf",&n,&a,&b);
    }
    MPI_Bcast( &n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast( &a, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast( &b, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    
    height = (b-a)/(double)n;
    local_n = n/comm_sz;
    local_a = a + my_rank*local_n*height;
    
    local_b = local_a + local_n*height;
    local_area = trapizoid(local_a,local_b,local_n,height);

    //cout<<my_rank<<endl;
    MPI_Reduce(&local_area, &total_area, 1, MPI_DOUBLE, MPI_SUM, 0,MPI_COMM_WORLD);

    //printing output

    if(my_rank==0)
        printf("With n = %d trapezoids, Our estimate of the integral from %f to %f = %.20f \n", n, a, b, total_area);

    MPI_Finalize();
    return 0;
}

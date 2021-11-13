#include <bits/stdc++.h>
#include <mpi.h>
using namespace std;

double func(double x)
{
    return x * x;
}

double trapizoid(double left_end, double right_end, int trap_count, double height)
{

    double segment_area, tmp;
    segment_area = (func(left_end) + func(right_end)) / 2.0;
    for (int i = 1; i < trap_count; i++)
    {
        segment_area += func(left_end + i * height);
    }
    segment_area *= height;

    return segment_area;
}

int main()
{
    int my_rank, comm_sz, n, local_n;
    double a, b, height, local_a, local_b, total_area, local_area;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    //input then bcast the data to all process
    if (my_rank == 0)
    {
        puts("Input number of process, starting point, ending point :");
        scanf("%d %lf %lf", &n, &a, &b);
    }
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&a, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(&b, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    height = (b - a) / (double)n;

    local_n = n / comm_sz;
    local_a = a + my_rank * local_n * height;

    if (my_rank == comm_sz - 1 && n % comm_sz != 0)
    {
        local_n = n % comm_sz; // while number of iteration is not divided by the process
    }

    local_b = local_a + local_n * height;
    local_area = trapizoid(local_a, local_b, local_n, height);

    MPI_Reduce(&local_area, &total_area, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (my_rank == 0)
        printf("With n = %d trapezoids, Our estimate of the integral from %f to %f is = %.20f \n", n, a, b, total_area);

    MPI_Finalize();
    return 0;
}
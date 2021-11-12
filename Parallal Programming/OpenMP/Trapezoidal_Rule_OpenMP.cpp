#include <bits/stdc++.h>

#ifdef _OPENMP
#include <omp.h>
#endif

using namespace std;

double f(double x)
{
    double return_val;

    return_val = x * x;
    return return_val;
} /* f */

double Trap(double a, double b, int n, int thread_count)
{
    double h, approx;
    int i;

    h = (b - a) / n;
    approx = (f(a) + f(b)) / 2.0;
#pragma omp parallel for num_threads(thread_count) \
    reduction(+: approx)
    for (i = 1; i <= n - 1; i++)
        approx += f(a + i * h);
    approx = h * approx;

    return approx;
}

int main(int argc, char *argv[])
{
    int n;
    double a, b;
    int thread_count = strtol(argv[1], NULL, 10);

    printf("Enter a, b, and n\n");
    scanf("%lf %lf %d", &a, &b, &n);

    double global_result = Trap(a, b, n, thread_count);

    printf("With n = %d trapezoids, our estimate\n", n);
    printf("of the integral from %f to %f = %.4f\n",a, b, global_result);
    return 0;
}

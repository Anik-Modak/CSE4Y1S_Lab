#include <bits/stdc++.h>

#ifdef _OPENMP
#include <omp.h>
#endif

using namespace std;

int thread_count;

void Print_list(int a[], int n)
{
    printf("After Sorting\n");
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n\n");
} /* Print_list */

void Read_list(int a[], int n)
{
    printf("Please enter the elements of the list\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
} /* Read_list */

void Odd_even(int a[], int n)
{
    int phase, i, tmp;
#pragma omp parallel num_threads(thread_count) default(none) shared(a, n) private(i, tmp, phase)
    for (phase = 0; phase < n; phase++)
    {
        if (phase % 2 == 0)
#pragma omp for
            for (i = 1; i < n; i += 2)
            {
                if (a[i - 1] > a[i])
                {
                    tmp = a[i - 1];
                    a[i - 1] = a[i];
                    a[i] = tmp;
                }
            }
        else
#pragma omp for
            for (i = 1; i < n - 1; i += 2)
            {
                if (a[i] > a[i + 1])
                {
                    tmp = a[i + 1];
                    a[i + 1] = a[i];
                    a[i] = tmp;
                }
            }
    }
} /* Odd_even */

int main(int argc, char *argv[])
{
    thread_count = strtol(argv[1], NULL, 10);

    double start, finish;
    int n, *a;
    printf("Size of the array: ");
    scanf("%d", &n);

    a = (int *)malloc(n * sizeof(int));

    Read_list(a, n);

    start = omp_get_wtime();
    Odd_even(a, n);
    finish = omp_get_wtime();

    Print_list(a, n);

    printf("Elapsed time = %e seconds\n", finish - start);
    free(a);
    return 0;
}

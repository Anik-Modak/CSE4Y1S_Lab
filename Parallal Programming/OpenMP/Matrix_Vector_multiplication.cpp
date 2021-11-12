#include <bits/stdc++.h>
#include <omp.h>

/* Serial functions */
void Get_args(int argc, char *argv[], int *thread_count_p,
              int *m_p, int *n_p);
void Usage(char *prog_name);
void Gen_matrix(double A[], int m, int n);
void Read_matrix(double A[], int m, int n);
void Gen_vector(double x[], int n);
void Read_vector(double x[], int n);
void Print_matrix(double A[], int m, int n);
void Print_vector(double y[], double m);

/* Parallel function */
void Omp_mat_vect(double A[], double x[], double y[],
                  int m, int n, int thread_count);

int main(int argc, char *argv[])
{
    int thread_count;
    int m, n;
    double *A;
    double *x;
    double *y;

    Get_args(argc, argv, &thread_count, &m, &n);

    A = (double *)malloc(m * n * sizeof(double));
    x = (double *)malloc(n * sizeof(double));
    y = (double *)malloc(m * sizeof(double));

    /*Read_matrix(A, m, n);
    Print_matrix(A, m, n);
    Read_vector(x, n);
    Print_vector(x, n);*/

    Gen_matrix(A, m, n);
    Print_matrix(A, m, n);
    Gen_vector(x, n);
    Print_vector(x, n);

    Omp_mat_vect(A, x, y, m, n, thread_count);
    Print_vector(y, m);

    free(A);
    free(x);
    free(y);

    return 0;
} /* main */

void Get_args(int argc, char *argv[], int *thread_count_p,
              int *m_p, int *n_p)
{

    if (argc != 4)
        Usage(argv[0]);
    *thread_count_p = strtol(argv[1], NULL, 10);
    *m_p = strtol(argv[2], NULL, 10);
    *n_p = strtol(argv[3], NULL, 10);
    if (*thread_count_p <= 0 || *m_p <= 0 || *n_p <= 0)
        Usage(argv[0]);

} /* Get_args */

void Usage(char *prog_name)
{
    fprintf(stderr, "usage: %s <thread_count> <m> <n>\n", prog_name);
    exit(0);
} /* Usage */

void Read_matrix(double A[], int m, int n)
{
    int i, j;
    printf("Enter the matrix\n");
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            scanf("%lf", &A[i * n + j]);
} /* Read_matrix */

void Gen_matrix(double A[], int m, int n)
{
    int i, j;
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            A[i * n + j] = random() / ((double)RAND_MAX);
} /* Gen_matrix */

void Gen_vector(double x[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        x[i] = random() / ((double)RAND_MAX);
} /* Gen_vector */

void Read_vector(double x[], int n)
{
    int i;
    printf("Enter the vector\n");
    for (i = 0; i < n; i++)
        scanf("%lf", &x[i]);
} /* Read_vector */

void Omp_mat_vect(double A[], double x[], double y[],
                  int m, int n, int thread_count)
{
    int i, j;
    double start, finish, elapsed;

    start = omp_get_wtime();
#pragma omp parallel for num_threads(thread_count) default(none) private(i, j) shared(A, x, y, m, n)
    for (i = 0; i < m; i++)
    {
        y[i] = 0.0;
        for (j = 0; j < n; j++)
            y[i] += A[i * n + j] * x[j];
    }
    finish = omp_get_wtime();
    elapsed = finish - start;
    printf("Elapsed time = %.5f seconds\n", elapsed);

} /* Omp_mat_vect */

void Print_matrix(double A[], int m, int n)
{
    int i, j;
    printf("We read\n");
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
            printf("%4.1f ", A[i * n + j]);
        printf("\n");
    }
} /* Print_matrix */

void Print_vector(double y[], double m)
{
    int i;
    printf("We read\n");
    for (i = 0; i < m; i++)
        printf("%4.1f ", y[i]);
    printf("\n");
} /* Print_vector */

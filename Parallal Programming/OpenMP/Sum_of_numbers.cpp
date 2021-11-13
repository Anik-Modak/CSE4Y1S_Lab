#include <bits/stdc++.h>
#include <time.h>
#ifdef _OPENMP
#include <omp.h>
#endif

using namespace std;

void serial(int n, int arr[])
{
    long long sum = 0;
    for (int i = 0; i < n; i++)
        sum += arr[i];

    cout << "Total sum: " << sum << endl;
}

void parallal(int n, int arr[], int thread_count)
{
    long long sum = 0;
#pragma omp parallel for num_threads(thread_count) reduction(+ \
                                                             : sum)
    for (int i = 0; i < n; i++)
        sum += arr[i];

    cout << "Total sum: " << sum << endl;
}

void Read_list(int a[], int n)
{
    printf("Please enter the elements of the list\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
} /* Read_list */

void Generate_list(int a[], int n) {
   srandom(1);
   for (int i = 0; i < n; i++)
      a[i] = random() % 100;
}

int main(int argc, char *argv[])
{
    int thread_count = strtol(argv[1], NULL, 10);

    int n, *arr;
    printf("Size of the array: ");
    scanf("%d", &n);

    arr = (int *)malloc(n * sizeof(int));
    //Read_list(arr, n);
    Generate_list(arr, n);

    clock_t begins = clock();
    serial(n, arr);
    clock_t ends = clock();

    double time_spents = (double)(ends - begins) / CLOCKS_PER_SEC;
    printf("Total time(Serial): %.5lf ms\n", time_spents * 1000.0);

    double beginp = omp_get_wtime();
    parallal(n, arr, thread_count);
    double endp = omp_get_wtime();

    double time_spentp = (double)(endp - beginp);
    printf("Total time(Palallel): %.5lf ms\n", time_spentp * 1000.0);
    return 0;
}

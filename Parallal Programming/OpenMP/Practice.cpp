#include<bits/stdc++.h>
#ifdef _OPENMP
#include <omp.h>
#endif
using namespace std;

int thread_count;
void Odd_even_sort(int a[], int n)
{
    int phase;
    #pragma omp parallel num_threads(thread_count) default(none) shared(a, n) private(phase)
    for(phase=0; phase < n; phase++)
    {
        if(phase%2==0)
        {
            #pragma omp for
            for(int i=1; i<n; i++)
                if(a[i] < a[i-1])
                    swap(a[i], a[i-1]);
        }
        else
        {
            #pragma omp for
            for(int i=1; i<n-1; i++)
                if(a[i] > a[i+1])
                    swap(a[i], a[i+1]);
        }
    }
}

void Print_list(int a[], int n)
{
    printf("After Sorting\n");
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n\n");
} /* Print_list */

int main(int argc,  char *argv[])
{
    thread_count = strtol(argv[1], NULL, 10);

    int n, *a;
    cout << "Enter size of array: ";
    cin >> n;

    a = (int *)malloc(n * sizeof(int));
    cout<<"Enter elements: ";
    for (int i = 0; i < n; i++)
        cin >> a[i];

    double t1, t2;
    t1 =  omp_get_wtime();
    Odd_even_sort(a, n);
    t2 =  omp_get_wtime();

    Print_list(a, n);
    printf("Elapsed time = %.5lf seconds\n", t2 - t1);
    free(a);
    return 0;
}
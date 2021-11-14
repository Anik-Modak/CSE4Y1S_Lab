#include <bits/stdc++.h>
#include <pthread.h>
#define MX 10005
using namespace std;

int thread_count;
int n, *a;
int part = 0, sum[MX] = {0};

void *sum_array(void *arg)
{
    int local_i = part++;
    for (int i = local_i * (n / thread_count); i < (local_i + 1) * (n / thread_count); i++)
        sum[local_i] += a[i];
    return NULL;
}

int main(int args, char *argv[])
{
    thread_count = strtol(argv[1], NULL, 10);
    cout << "Enter size of array: ";
    cin >> n;

    a = (int *)malloc(n * sizeof(int));
    cout<<"Enter elements: ";
    for (int i = 0; i < n; i++)
        cin >> a[i];

    clock_t begin = clock();
    pthread_t threads[thread_count];
    for (int i = 0; i < thread_count; i++)
        pthread_create(&threads[i], NULL, sum_array, (void *)NULL);

    for (int i = 0; i < thread_count; i++)
        pthread_join(threads[i], NULL);

    int total_sum = 0;
    for (int i = 0; i < thread_count; i++)
        total_sum += sum[i];

    clock_t end = clock();
    double time = (double)(end - begin) / CLOCKS_PER_SEC;

    cout << "Sum is: " << total_sum << endl;
    printf("Total time: %.5lf ms\n", time * 10000);
    return 0;
}
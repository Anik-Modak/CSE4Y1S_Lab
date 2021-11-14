#include <bits/stdc++.h>
#include <pthread.h>
using namespace std;

int thread_count;
int n, *a;
int sum[10] = {0};
int part = 0;

void *sum_array(void *arg)
{
    int thread_part = part++;
    for (int i = thread_part * (n / thread_count); i < (thread_part + 1) * (n / thread_count); i++)
        sum[thread_part] += a[i];
    return NULL;
}

void Read_list(void)
{
    printf("Please enter the elements of the list\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
} /* Read_list */

int main(int argc, char *argv[])
{
    printf("Size of the array: ");
    scanf("%d", &n);

    thread_count = strtol(argv[1], NULL, 10);
    a = (int *)malloc(n * sizeof(int));
    Read_list();

    pthread_t threads[thread_count];

    clock_t begin = clock();
    for (int i = 0; i < thread_count; i++)
        pthread_create(&threads[i], NULL, sum_array, (void *)NULL);

    for (int i = 0; i < thread_count; i++)
        pthread_join(threads[i], NULL);

    int total_sum = 0;
    for (int i = 0; i < thread_count; i++)
        total_sum += sum[i];

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    cout << "sum is: " << total_sum << endl;
    printf("Total time: %.5lf ms\n", time_spent * 1000.0);

    return 0;
}

#include <bits/stdc++.h>
#include <mpi.h>
using namespace std;

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

void Bubble_sort(int a[], int n)
{
   int list_length, i, temp;
   for (list_length = n; list_length > 1; list_length--)
      for (i = 0; i < list_length-1; i++)
         if (a[i] > a[i+1]) 
            swap(a[i], a[i+1]);
} /* Bubble_sort */

int main()
{
    int n, *a;
    printf("Size of the array: ");
    scanf("%d",&n);

    a = (int *)malloc(n * sizeof(int));

    Read_list(a, n);

    Bubble_sort(a, n);

    Print_list(a, n);

    free(a);
    return 0;
} /* main */
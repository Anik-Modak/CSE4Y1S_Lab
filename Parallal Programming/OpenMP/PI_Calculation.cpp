#include <bits/stdc++.h>

#ifdef _OPENMP
#include <omp.h>
#endif

using namespace std;

int main(int argc, char *argv[])
{
    int thread_count = strtol(argv[1], NULL, 10);

    long long i, n = 10000;
    double sum = 0.0, factor;

#pragma omp parallel num_threads(thread_count) default(none) reduction(+ \
                                                                       : sum) private(i, factor) shared(n)
    for (i = 0; i < n; i++)
    {
        factor = (i % 2 == 0) ? 1.0 : -1.0;
        sum += factor / (2 * i + 1);
    }

    double pi_approx = (sum * 4.0)/thread_count;
    cout << "PI : " << pi_approx << endl;

    return 0;
}

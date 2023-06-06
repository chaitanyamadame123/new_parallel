#include <stdio.h>
#include <omp.h>

#define n 900000000

int main()
{
    int i;
    double step, result = 0.0, start_t, end_t, exec_t;
    double x, pi, sum = 0.0;

    step = 1.0 / (double)n;

    start_t = omp_get_wtime();

    #pragma omp parallel for reduction(+:sum)
    for (i = 0; i < n; i++)
    {
        x = (i)*step;
        sum = sum + 4.0 / (1.0 + x * x);
    }

    pi = step * sum;

    end_t = omp_get_wtime();
    exec_t = end_t - start_t;

    printf("\n sum = %f\n", pi);
    printf("\n Execution time = %f\n", exec_t);

    return 0;
}

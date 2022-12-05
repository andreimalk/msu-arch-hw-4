#include <stdio.h>
#include <omp.h>
#include <thread>

std::chrono::milliseconds timeout(150);

void test(int first, int last)
{
#pragma omp for schedule(static) ordered
    for (int i = first; i <= last; ++i) {
        std::this_thread::sleep_for(timeout);
        if (i % 2)
        {
#pragma omp ordered
            printf_s("test1() iteration %d\n", i);
        }
    }
}

void test2(int iter)
{
#pragma omp ordered
    printf_s("test2() iteration %d\n", iter);
}

int main( )
{
    int i;
#pragma omp parallel
    {
        test(1, 10);
#pragma omp for ordered
        for (i = 0 ; i <= 5 ; i++)
            test2(i);
    }
}
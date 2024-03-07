#include "fibonacci.h"

int64_t CalculateNthFibonacci(int64_t n) {
    int64_t fib_prev = 0;
    int64_t fib_cur = 1;
    for (; n > 0; --n) {
        int64_t fib_new = fib_prev + fib_cur;
        fib_prev = fib_cur;
        fib_cur = fib_new;
    }
    return fib_prev;
}
#include "min_divisor.h"

int64_t MinDivisor(int64_t number) {
    if (number < 0) {
        number = -number;
    }
    if (number % 2 == 0) {
        return 2;
    }

    for (int64_t div = 3; div * div <= number; div += 2) {
        if (number % div == 0) {
            // div <= sqrt(number) <= number / div
            // div is smaller than number / div
            return div;
        }
    }

    // number is prime
    return number;
}
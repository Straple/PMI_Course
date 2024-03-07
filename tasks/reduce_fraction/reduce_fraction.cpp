#include "reduce_fraction.h"
#include <numeric>

int64_t ReduceFraction(int64_t numerator, int64_t denominator) {
    if (denominator < 0) {
        numerator = -numerator;
        denominator = -denominator;
    }
    int64_t gcd = std::gcd(numerator, denominator);
    return (numerator + denominator) / gcd;
}

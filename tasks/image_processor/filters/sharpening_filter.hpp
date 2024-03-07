#pragma once

#include "matrix_filter.hpp"

struct SharpeningFilter final : MatrixFilter {
    const static inline std::vector<std::vector<double>> MATRIX_DATA = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};
    SharpeningFilter();
};
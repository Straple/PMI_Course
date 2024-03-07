#pragma once

#include "complex_filter.hpp"

struct MatrixFilterException : FilterException {
    explicit MatrixFilterException(const std::string& message);
};

struct InvalidMatrixInitialization : MatrixFilterException {
    explicit InvalidMatrixInitialization(const std::string& message);
};

class MatrixFilter : public ComplexFilter {
    std::vector<std::vector<double>> matrix_;

public:
    explicit MatrixFilter(std::vector<std::vector<double>> matrix);

    RGB CalcFilter(const Image& image, int row, int column) override;
};
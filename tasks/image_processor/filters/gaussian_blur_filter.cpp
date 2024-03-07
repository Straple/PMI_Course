#include "gaussian_blur_filter.hpp"

#include "matrix_filter.hpp"
#include <cmath>

GaussianBlurFilter::GaussianBlurFilter(double sigma) : sigma_(sigma) {
}

void GaussianBlurFilter::operator()(Image& image) {
    const static double PI = 3.14159265358979323846L;
    const static double E = 2.71828182845904523536L;

    const int matrix_half = static_cast<int>(
        std::min(std::ceil(3 * sigma_), static_cast<double>(std::max(image.Height(), image.Width())) / 2 + 1));

    std::vector<double> coef(matrix_half * 3);
    for (uint32_t index = 0; index < coef.size(); index++) {
        coef[index] = std::pow(E, -(1.0 * index * index / (2 * sigma_ * sigma_)));
    }

    {
        std::vector<std::vector<double>> matrix(1, std::vector<double>(2 * matrix_half));

        const double magic_factor = (1.0 / (2 * PI * sigma_ * sigma_));
        for (int index = 0; index < 2 * matrix_half; index++) {
            matrix[0][index] = coef[std::abs(index - matrix_half)] * magic_factor;
        }

        MatrixFilter row_filter(matrix);

        row_filter(image);
    }

    {
        std::vector<std::vector<double>> matrix(2 * matrix_half, std::vector<double>(1));

        for (int index = 0; index < 2 * matrix_half; index++) {
            matrix[index][0] = coef[std::abs(index - matrix_half)];
        }

        MatrixFilter column_filter(matrix);

        column_filter(image);
    }
}
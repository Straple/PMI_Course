#include "matrix_filter.hpp"

MatrixFilterException::MatrixFilterException(const std::string& message)
    : FilterException("Matrix filter exception: " + message) {
}

InvalidMatrixInitialization::InvalidMatrixInitialization(const std::string& message)
    : MatrixFilterException("Invalid matrix initialization: " + message) {
}

MatrixFilter::MatrixFilter(std::vector<std::vector<double>> matrix) : matrix_(std::move(matrix)) {
    for (const auto& row : matrix_) {
        if (row.size() != matrix_.begin()->size()) {
            throw InvalidMatrixInitialization("got matrix is not matrix :)\nlines are not the same length");
        }
    }
}

RGB MatrixFilter::CalcFilter(const Image& image, int row, int column) {
    row -= static_cast<int>(matrix_.size()) / 2;
    if (!matrix_.empty()) {
        column -= static_cast<int>(matrix_[0].size()) / 2;
    }
    RGB color;
    for (int matrix_row = 0; matrix_row < static_cast<int>(matrix_.size()); matrix_row++) {
        for (int matrix_column = 0; matrix_column < static_cast<int>(matrix_[0].size()); matrix_column++) {
            color += matrix_[matrix_row][matrix_column] * image(row + matrix_row, column + matrix_column);
        }
    }
    color.Normalize();
    return color;
}
#include "complex_filter.hpp"

void ComplexFilter::operator()(Image& image) {
    Image result;
    result.Resize(image.Height(), image.Width());
    for (int row = 0; row < static_cast<int>(image.Height()); row++) {
        for (int column = 0; column < static_cast<int>(image.Width()); column++) {
            result(row, column) = CalcFilter(image, row, column);
        }
    }
    image = std::move(result);
}
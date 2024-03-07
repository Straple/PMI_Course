#include "base_filter.hpp"

FilterException::FilterException(const std::string& message) : std::runtime_error("Filter exception: " + message) {
}

RGB BaseFilter::CalcFilter(const Image& image, int row, int column) {
    return image(row, column);
}

void BaseFilter::operator()(Image& image) {
    for (int row = 0; row < static_cast<int>(image.Height()); row++) {
        for (int column = 0; column < static_cast<int>(image.Width()); column++) {
            image(row, column) = CalcFilter(image, row, column);
        }
    }
}
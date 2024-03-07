#include "single_pixel_filter.hpp"

RGB SinglePixelFilter::CalcFilter(RGB color) {
    return color;
}

RGB SinglePixelFilter::CalcFilter(const Image& image, int row, int column) {
    return CalcFilter(image(row, column));
}
#include "negative_filter.hpp"

RGB NegativeFilter::CalcFilter(RGB color) {
    color.red = 1 - color.red;
    color.green = 1 - color.green;
    color.blue = 1 - color.blue;
    return color;
}
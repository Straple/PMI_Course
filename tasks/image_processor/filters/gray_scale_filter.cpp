#include "gray_scale_filter.hpp"

RGB GrayScaleFilter::CalcFilter(RGB color) {
    const static double FACTOR_FOR_RED = 0.299;
    const static double FACTOR_FOR_GREEN = 0.587;
    const static double FACTOR_FOR_BLUE = 0.114;
    color.red = color.blue = color.green =
        FACTOR_FOR_RED * color.red + FACTOR_FOR_GREEN * color.green + FACTOR_FOR_BLUE * color.blue;
    return color;
}
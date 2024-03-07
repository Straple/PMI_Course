#include "rgb.hpp"
#include "rgb24.hpp"
#include <algorithm>

RGB::RGB(RGB24 color) {
    blue = static_cast<double>(color.blue) / RGB24::MAX_VAL;
    green = static_cast<double>(color.green) / RGB24::MAX_VAL;
    red = static_cast<double>(color.red) / RGB24::MAX_VAL;
}

RGB& operator*=(RGB& color, double factor) {
    color.red *= factor;
    color.green *= factor;
    color.blue *= factor;
    return color;
}

RGB operator*(RGB color, double factor) {
    return color *= factor;
}

RGB operator*(double factor, RGB color) {
    return color *= factor;
}

RGB& operator+=(RGB& lhs, const RGB& rhs) {
    lhs.red += rhs.red;
    lhs.green += rhs.green;
    lhs.blue += rhs.blue;
    return lhs;
}

RGB operator+(RGB lhs, const RGB& rhs) {
    return lhs += rhs;
}

RGB& operator-=(RGB& lhs, const RGB& rhs) {
    lhs.red -= rhs.red;
    lhs.green -= rhs.green;
    lhs.blue -= rhs.blue;
    return lhs;
}

RGB operator-(RGB lhs, const RGB& rhs) {
    return lhs -= rhs;
}

void RGB::Normalize() {
    red = std::clamp(red, 0.0, 1.0);
    green = std::clamp(green, 0.0, 1.0);
    blue = std::clamp(blue, 0.0, 1.0);
}
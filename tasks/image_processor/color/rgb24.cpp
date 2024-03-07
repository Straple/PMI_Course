#include "rgb24.hpp"
#include "rgb.hpp"

RGB24::RGB24(RGB color) {
    blue = static_cast<uint8_t>(color.blue * MAX_VAL);
    green = static_cast<uint8_t>(color.green * MAX_VAL);
    red = static_cast<uint8_t>(color.red * MAX_VAL);
}
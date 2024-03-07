#pragma once

#include "single_pixel_filter.hpp"

struct GrayScaleFilter final : SinglePixelFilter {
    RGB CalcFilter(RGB color) override;
};
#pragma once

#include "single_pixel_filter.hpp"

struct NegativeFilter final : SinglePixelFilter {
    RGB CalcFilter(RGB color) override;
};
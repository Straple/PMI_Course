#pragma once

#include "base_filter.hpp"

struct SinglePixelFilter : BaseFilter {
    virtual RGB CalcFilter(RGB color);

    RGB CalcFilter(const Image& image, int row, int column) final;
};
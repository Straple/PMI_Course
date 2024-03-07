#pragma once

#include "single_pixel_filter.hpp"

class ThresholdFilter final : public SinglePixelFilter {
    double threshold_ = 0;

public:
    explicit ThresholdFilter(double threshold);

    RGB CalcFilter(RGB color) final;
};

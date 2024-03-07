#pragma once

#include "complex_filter.hpp"

class EdgeDetectionFilter final : public ComplexFilter {
    double threshold_ = 0;

public:
    explicit EdgeDetectionFilter(double threshold);

    void operator()(Image& image) final;
};

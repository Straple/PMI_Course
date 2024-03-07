#pragma once

#include "complex_filter.hpp"

class GaussianBlurFilter final : public ComplexFilter {
    double sigma_ = 0;

public:
    explicit GaussianBlurFilter(double sigma);

    void operator()(Image& image) final;
};
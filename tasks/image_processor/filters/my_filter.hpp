#pragma once

#include "base_filter.hpp"

struct MyFilterException : FilterException {
    explicit MyFilterException(const std::string& message);
};

class MyFilter final : public BaseFilter {
    double blur_sigma_;
    double max_dist_;
    double max_diff_;

public:
    MyFilter(double blur_sigma, double max_dist, double max_diff);
    void operator()(Image& image) final;
};
#pragma once

#include "../image/image.hpp"

struct FilterException : std::runtime_error {
    explicit FilterException(const std::string& message);
};

struct BaseFilter {
    virtual RGB CalcFilter(const Image& image, int row, int column);

    virtual void operator()(Image& image);
};
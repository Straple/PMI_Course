#pragma once

#include "base_filter.hpp"

struct ComplexFilter : BaseFilter {
    void operator()(Image& image) override;
};
#include "threshold_filter.hpp"

ThresholdFilter::ThresholdFilter(double threshold) : threshold_(threshold) {
}

RGB ThresholdFilter::CalcFilter(RGB color) {
    auto accept_threshold = [&](double value) {
        if (value > threshold_) {
            return 1;
        } else {
            return 0;
        }
    };

    color.red = accept_threshold(color.red);
    color.green = accept_threshold(color.green);
    color.blue = accept_threshold(color.blue);
    return color;
}
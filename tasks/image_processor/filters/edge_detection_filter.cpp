#include "edge_detection_filter.hpp"

#include "gray_scale_filter.hpp"
#include "matrix_filter.hpp"
#include "threshold_filter.hpp"

EdgeDetectionFilter::EdgeDetectionFilter(double threshold) : threshold_(threshold) {
}

void EdgeDetectionFilter::operator()(Image& image) {
    GrayScaleFilter()(image);

    static MatrixFilter filter({{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}});
    filter(image);

    ThresholdFilter threshold_filter(threshold_);
    threshold_filter(image);
}

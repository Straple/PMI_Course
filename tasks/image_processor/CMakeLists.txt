add_executable(
    image_processor
    image_processor.cpp
        color/rgb24.cpp
        color/rgb.cpp

        bitmap/bitmap_file_header.cpp
        bitmap/bitmap_info.cpp

        image/image_exception.cpp
        image/image.cpp

        filters/base_filter.cpp
        filters/single_pixel_filter.cpp
        filters/complex_filter.cpp
        filters/matrix_filter.cpp
        filters/gray_scale_filter.cpp
        filters/negative_filter.cpp
        filters/threshold_filter.cpp
        filters/sharpening_filter.cpp
        filters/edge_detection_filter.cpp
        filters/gaussian_blur_filter.cpp
        filters/my_filter.cpp

    interpreter.cpp
)

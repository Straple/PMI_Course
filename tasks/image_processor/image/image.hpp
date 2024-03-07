#pragma once

#include <stdexcept>
#include <string>
#include <vector>

#include "../color/rgb.hpp"
#include <iostream>
#include "image_exception.hpp"

class Image {
    uint32_t m_height_ = 0;
    uint32_t m_width_ = 0;
    std::vector<std::vector<RGB>> m_matrix_;

    void BuildMatrix(const std::vector<char> &buffer);

public:
    uint32_t Height() const;

    uint32_t Width() const;

    void Read(const std::string &filename);

    void Write(const std::string &filename) const;

    void Clear();

    void Resize(uint32_t height, uint32_t width);

    [[nodiscard]] Image Crop(int left, int top, int crop_height, int crop_width) const;

    RGB &operator()(int row, int column);

    const RGB &operator()(int row, int column) const;
};

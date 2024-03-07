#include "image.hpp"
#include "../bitmap/bitmap_info.hpp"
#include "../bitmap/bitmap_file_header.hpp"
#include "../color/rgb24.hpp"
#include <cassert>
#include <fstream>
#include <iostream>

void Image::BuildMatrix(const std::vector<char> &buffer) {
    m_matrix_.resize(m_height_);
    for (uint32_t row = 0; row < m_height_; row++) {
        const RGB24 *pixels_row = reinterpret_cast<const RGB24 *>(
            buffer.data() + static_cast<std::size_t>(row * (m_width_ * 3 + m_width_ % 4)));
        for (uint32_t column = 0; column < m_width_; column++) {
            auto &matrix_row = m_matrix_[m_height_ - row - 1];
            matrix_row.resize(m_width_);
            matrix_row[column] = RGB(pixels_row[column]);
        }
    }
}

void Image::Clear() {
    m_height_ = m_width_ = 0;
    m_matrix_.clear();
}

void Image::Read(const std::string &filename) {
    Clear();

    std::ifstream file_input(filename, std::ios_base::in | std::ios_base::binary);

    if (!file_input.is_open()) {
        throw UnableToOpenFileException(filename);
    }

    file_input.exceptions(std::ios_base::failbit | std::ios_base::badbit);

    BitmapFileHeader file_header;
    file_header.Read(file_input);

    BitmapInfo file_bitmap_info;
    file_bitmap_info.Read(file_input);

    std::vector<char> buffer(file_bitmap_info.biSizeImage);

    // не требуется, так как есть гарантия, что сразу после заголовков идет
    file_input.seekg(file_header.bfOffBits, std::ios::beg);

    file_input.read(buffer.data(), file_bitmap_info.biSizeImage);

    m_height_ = file_bitmap_info.biHeight;
    m_width_ = file_bitmap_info.biWidth;
    BuildMatrix(buffer);
}

void Image::Write(const std::string &filename) const {
    std::ofstream file_output(filename, std::ios_base::out | std::ios_base::binary);

    if (!file_output.is_open()) {
        throw UnableToOpenFileException(filename);
    }

    file_output.exceptions(std::ios_base::failbit | std::ios_base::badbit);

    BitmapFileHeader file_header;
    file_header.Write(file_output, m_height_, m_width_);

    BitmapInfo file_bitmap_info;
    file_bitmap_info.Write(file_output, m_height_, m_width_);

    for (uint32_t row = m_height_; row > 0; row--) {
        for (uint32_t column = 0; column < m_width_; column++) {
            RGB24 color = RGB24(m_matrix_[row - 1][column]);
            file_output.write(reinterpret_cast<char *>(&color), 3);
        }
        for (uint32_t i = 0; i < m_width_ % 4; i++) {
            file_output.write("\0", 1);
        }
    }
}

uint32_t Image::Height() const {
    return m_height_;
}
uint32_t Image::Width() const {
    return m_width_;
}

void Image::Resize(uint32_t height, uint32_t width) {
    m_height_ = height;
    m_width_ = width;
    m_matrix_.resize(height);
    for (uint32_t row = 0; row < height; row++) {
        m_matrix_[row].resize(width);
    }
}

Image Image::Crop(int left, int top, int crop_height, int crop_width) const {
    left = std::clamp(left, 0, static_cast<int>(m_width_));
    top = std::clamp(top, 0, static_cast<int>(m_height_));
    crop_height = std::clamp(crop_height, 0, static_cast<int>(m_height_) - 1 - top);
    crop_width = std::clamp(crop_width, 0, static_cast<int>(m_width_) - 1 - left);

    Image result;
    result.Resize(crop_height, crop_width);
    for (int row = 0; row < crop_height; row++) {
        for (int column = 0; column < crop_width; column++) {
            result.m_matrix_[row][column] = m_matrix_[row + top][column + left];
        }
    }
    return result;
}

RGB &Image::operator()(int row, int column) {
    row = std::clamp(row, 0, static_cast<int>(m_height_) - 1);
    column = std::clamp(column, 0, static_cast<int>(m_width_) - 1);
    return m_matrix_[row][column];
}

const RGB &Image::operator()(int row, int column) const {
    row = std::clamp(row, 0, static_cast<int>(m_height_) - 1);
    column = std::clamp(column, 0, static_cast<int>(m_width_) - 1);
    return m_matrix_[row][column];
}

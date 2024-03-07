#pragma once

#include <cstdint>
#include <iostream>

#include "../image/image_exception.hpp"

struct Reserved1IsNotZeroException : InvalidBmpFormatException {
    explicit Reserved1IsNotZeroException(int reserved1);
};

struct Reserved2IsNotZeroException : InvalidBmpFormatException {
    explicit Reserved2IsNotZeroException(int reserved2);
};

#pragma pack(push, 1)

struct BitmapFileHeader {
    // NOLINTBEGIN(misc-non-private-member-variables-in-classes)
    uint16_t bfType = 0;
    uint32_t bfSize = 0;
    uint16_t bfReserved1 = 0;
    uint16_t bfReserved2 = 0;
    uint32_t bfOffBits = 0;
    // NOLINTEND(misc-non-private-member-variables-in-classes)

    void Read(std::istream &input);

    void Write(std::ostream &output, uint32_t image_height, uint32_t image_width);
};

const static inline int EXPECTED_BITMAP_FILE_HEADER_SIZEOF = 14;
static_assert(sizeof(BitmapFileHeader) == EXPECTED_BITMAP_FILE_HEADER_SIZEOF);

#pragma pack(pop)
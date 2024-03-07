#pragma once

#include <cstdint>
#include <iostream>
#include "../image/image_exception.hpp"

struct InvalidBmpVersionException : InvalidBmpFormatException {
    explicit InvalidBmpVersionException(unsigned int header_size);
};

struct NotPositiveHeightException : InvalidBmpFormatException {
    explicit NotPositiveHeightException(int height);
};

struct NotPositiveWidthException : InvalidBmpFormatException {
    explicit NotPositiveWidthException(int width);
};

struct InvalidPlanesException : InvalidBmpFormatException {
    explicit InvalidPlanesException(int planes);
};

struct InvalidBitsCountPerPixelException : InvalidBmpFormatException {
    explicit InvalidBitsCountPerPixelException(int bit_count);
};

struct ColorPaletteIsUnsupportedException : InvalidBmpFormatException {
    explicit ColorPaletteIsUnsupportedException();
};

#pragma pack(push, 1)

struct BitmapInfo {
    // NOLINTBEGIN(misc-non-private-member-variables-in-classes)
    uint32_t biSize = 0;
    int32_t biWidth = 0;
    int32_t biHeight = 0;
    uint16_t biPlanes = 0;
    uint16_t biBitCount = 0;
    uint32_t biCompression = 0;
    uint32_t biSizeImage = 0;
    int32_t biXPelsPerMeter = 0;
    int32_t biYPelsPerMeter = 0;
    uint32_t biClrUsed = 0;
    uint32_t biClrlImportant = 0;
    // NOLINTEND(misc-non-private-member-variables-in-classes)

    void Read(std::istream &input);

    void Write(std::ostream &output, uint32_t image_height, uint32_t image_width);
};

const static int EXPECTED_BITMAP_INFO_SIZEOF = 40;
static_assert(sizeof(BitmapInfo) == EXPECTED_BITMAP_INFO_SIZEOF);

#pragma pack(pop)

#include "bitmap_info.hpp"
#include "../color/rgb24.hpp"

InvalidBmpVersionException::InvalidBmpVersionException(unsigned int header_size)
    : InvalidBmpFormatException(
          "Invalid BMP: expected version 3 and header size 40, but header "
          "size is " +
          std::to_string(header_size)) {
}

NotPositiveHeightException::NotPositiveHeightException(int height)
    : InvalidBmpFormatException("Invalid BMP: expected positive biHeight, got " + std::to_string(height)) {
}

NotPositiveWidthException::NotPositiveWidthException(int width)
    : InvalidBmpFormatException("Invalid BMP: expected positive biWidth, got " + std::to_string(width)) {
}

InvalidPlanesException::InvalidPlanesException(int planes)
    : InvalidBmpFormatException("Invalid BMP: expected biPlanes=1, got " + std::to_string(planes)) {
}

InvalidBitsCountPerPixelException::InvalidBitsCountPerPixelException(int bit_count)
    : InvalidBmpFormatException("Invalid BMP: expected 24 bits per pixel, got " + std::to_string(bit_count)) {
}

ColorPaletteIsUnsupportedException::ColorPaletteIsUnsupportedException()
    : InvalidBmpFormatException("Invalid BMP: color palette is unsupported") {
}

void BitmapInfo::Read(std::istream &input) {
    input.read(reinterpret_cast<char *>(this), sizeof(BitmapInfo));

    if (biSizeImage == 0) {
        // может быть обнулено
        biSizeImage = biHeight * (biWidth * sizeof(RGB24) + biWidth % 4);
    }

    const static int EXPECTED_BI_SIZE = 40;
    if (biSize != EXPECTED_BI_SIZE) {
        throw InvalidBmpVersionException(biSize);
    }
    if (biHeight <= 0) {
        throw NotPositiveHeightException(biHeight);
    }
    if (biWidth <= 0) {
        throw NotPositiveWidthException(biWidth);
    }
    if (biPlanes != 1) {
        throw InvalidPlanesException(biPlanes);
    }

    const static int EXPECTED_BIT_COUNT = 24;
    if (biBitCount != EXPECTED_BIT_COUNT) {
        throw InvalidBitsCountPerPixelException(biBitCount);
    }
    if (biClrUsed != 0) {
        // есть таблица цветов
        throw ColorPaletteIsUnsupportedException();
    }
}

void BitmapInfo::Write(std::ostream &output, uint32_t image_height, uint32_t image_width) {
    const static int BITS_COUNT_IN_BYTE = 8;

    biSize = sizeof(BitmapInfo);
    biWidth = static_cast<int32_t>(image_width);
    biHeight = static_cast<int32_t>(image_height);
    biPlanes = 1;
    biBitCount = sizeof(RGB24) * BITS_COUNT_IN_BYTE;
    biCompression = 0;
    biSizeImage = image_height * (image_width * sizeof(RGB24) + image_width % 4);
    biXPelsPerMeter = 0;
    biYPelsPerMeter = 0;
    biClrUsed = 0;
    biClrlImportant = 0;

    output.write(reinterpret_cast<char *>(this), sizeof(BitmapInfo));
}
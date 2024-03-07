#include "bitmap_file_header.hpp"

#include "bitmap_info.hpp"
#include "../color/rgb24.hpp"

Reserved1IsNotZeroException::Reserved1IsNotZeroException(int reserved1)
    : InvalidBmpFormatException("Invalid BMP: expected bfReserved1=0, got " + std::to_string(reserved1)) {
}

Reserved2IsNotZeroException::Reserved2IsNotZeroException(int reserved2)
    : InvalidBmpFormatException("Invalid BMP: expected bfReserved2=0, got " + std::to_string(reserved2)) {
}

void BitmapFileHeader::Read(std::istream &input) {
    input.read(reinterpret_cast<char *>(this), sizeof(BitmapFileHeader));

    if (bfReserved1 != 0) {
        throw Reserved1IsNotZeroException(bfReserved1);
    }
    if (bfReserved2 != 0) {
        throw Reserved2IsNotZeroException(bfReserved2);
    }
}

void BitmapFileHeader::Write(std::ostream &output, uint32_t image_height, uint32_t image_width) {
    const static uint16_t BF_TYPE_MAGIC_VALUE = 19778;
    bfType = BF_TYPE_MAGIC_VALUE;
    bfSize = sizeof(BitmapFileHeader) + sizeof(BitmapInfo) +
             static_cast<uint64_t>(image_height) * (image_width * sizeof(RGB24) + image_width % 4);
    bfReserved1 = bfReserved2 = 0;
    bfOffBits = sizeof(BitmapFileHeader) + sizeof(BitmapInfo);

    output.write(reinterpret_cast<char *>(this), sizeof(BitmapFileHeader));
}
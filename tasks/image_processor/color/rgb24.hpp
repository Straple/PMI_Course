#pragma once

#include <cstdint>

struct RGB;

#pragma pack(push, 1)

struct RGB24 {
    uint8_t blue = 0;
    uint8_t green = 0;
    uint8_t red = 0;

    const static inline uint8_t MAX_VAL = 255;

    RGB24() = default;

    explicit RGB24(RGB color);
};

const static inline int EXPECTED_RGB24_SIZEOF = 3;
static_assert(sizeof(RGB24) == EXPECTED_RGB24_SIZEOF);

#pragma pack(pop)

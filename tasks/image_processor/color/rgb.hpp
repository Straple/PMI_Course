#pragma once

struct RGB24;

struct RGB {
    double blue = 0;
    double green = 0;
    double red = 0;

    RGB() = default;

    explicit RGB(RGB24 color);

    void Normalize();
};

RGB& operator*=(RGB& color, double factor);

RGB operator*(RGB color, double factor);

RGB operator*(double factor, RGB color);

RGB& operator+=(RGB& lhs, const RGB& rhs);

RGB operator+(RGB lhs, const RGB& rhs);

RGB& operator-=(RGB& lhs, const RGB& rhs);

RGB operator-(RGB lhs, const RGB& rhs);

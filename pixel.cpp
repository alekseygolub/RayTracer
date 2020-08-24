#include "pixel.h"

Pixel::Pixel(double r, double g, double b): r(r), g(g), b(b) {}

RGBApixel Pixel::toBMPPixel(double light) {
    RGBApixel ans;
    ans.Alpha = 0;
    ans.Green = std::min(255.0, g * light);
    ans.Blue = std::min(255.0, b * light);
    ans.Red = std::min(255.0, r * light);
    return ans;
}

Pixel Pixel::operator+(Pixel p) {
    return Pixel(r + p.r, g + p.g, b + p.b);
}

Pixel Pixel::operator*(double k) {
    return Pixel(r * k, g * k, b * k);
}


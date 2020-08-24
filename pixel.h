#ifndef PIXEL_H
#define PIXEL_H
#include "EasyBMP.h"

struct Pixel {
    double r, g, b;

    Pixel(double r = 0, double g = 0, double b = 0);

    Pixel operator+(Pixel p);

    Pixel operator*(double k);

    RGBApixel toBMPPixel(double light = 1);
};

#endif // PIXEL_H

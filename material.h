#ifndef MATERIAL_H
#define MATERIAL_H

#include "pixel.h"

struct Material {
    Pixel color;
    double reflect, light;

    Material() = default;
    
    Material(Pixel c, double r, double l);
};

#endif // MATERIAL_H

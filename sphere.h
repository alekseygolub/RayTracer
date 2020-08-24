#ifndef SPHERE_H
#define SPHERE_H

#include "point.h"
#include "material.h"

struct Sphere {
    Point center;
    double r;
    Material mat;

    Sphere() = default;

    Sphere(Point, double, Material);

    Point get_normal(Point p);

    double dist(Point p);
};

#endif // SPHERE_H

#ifndef RAY_H
#define RAY_H

#include "point.h"

struct Ray {
    Point pos, dir;

    Ray() = default;

    Ray(Point, Point);

    void move(double dist);
};

#endif // RAY_H

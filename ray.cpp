#include "ray.h"

Ray::Ray(Point pos, Point der): pos(pos), dir(der) {
    der.normalize();
}

void Ray::move(double dist) {
    dir.normalize();
    pos = pos + dir * dist;
}


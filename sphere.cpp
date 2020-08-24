#include "sphere.h"
#include <cmath>

Sphere::Sphere(Point c, double r, Material m): center(c), r(r), mat(m) {}

Point Sphere::get_normal(Point p) {
    return p - center;
}

double Sphere::dist(Point p) {
    return fabs(get_normal(p).len() - r);
}

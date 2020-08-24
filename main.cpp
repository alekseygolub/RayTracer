#include <iostream>
#include <vector>
#include "sphere.h"
#include "ray.h"
#include "pixel.h"
#include <cmath>
#include "EasyBMP.h"

using namespace std;

const double EPS = 1e-4;
const int MAX_DEEP = 200;

int foo = 0;
bool debug = 0;

pair<double, double> solve_sqr_eq(double a, double b, double c) {
    double d = b * b - 4 * a * c;
    if (d < 0) {
        return {NAN, NAN};
    }
    return {(-b + sqrt(d)) / (2 * a), (-b - sqrt(d)) / (2 * a)};
}

vector<pair<Point, double>> lights;
vector<Sphere> scene;

pair<double, int> get_min_distance(Ray r) {
    int num = -1;
    double t = NAN;
    r.dir.normalize();
    for (int i = 0; i < (int)scene.size(); i++) {
        auto pos = r.pos;
        auto center = scene[i].center;
        auto dir = r.dir;

        auto dst = solve_sqr_eq(1, 2 * (pos * dir - center * dir), pow(pos.len(), 2) + pow(center.len(), 2) - pos * center * 2 - scene[i].r * scene[i].r);
        if (!isnan(dst.first) && dst.first >= 0) {
            if (num == -1 || t > dst.first) {
                num = i;
                t = dst.first;
            }
        }
        if (!isnan(dst.first) && dst.second >= 0) {
            if (num == -1 || t > dst.second) {
                num = i;
                t = dst.second;
            }
        }
    }
    return {t, num};
}

Pixel trace(Ray r, double refl = 1., int deep = 0.) {
    if (refl <= EPS || deep >= MAX_DEEP) {
        return Pixel();
    }
    int num;
    double t;
    auto dst = get_min_distance(r);
    t = dst.first;
    num = dst.second;
    if (num == -1) {
        return Pixel();
    }
    r.move(t);
    Point norm = scene[num].get_normal(r.pos);
    norm.normalize();
    r.dir = r.dir.rotate(norm, M_PI) * -1;
    double light = 0;
    for (auto &x: lights) {
        Ray tr(r.pos, x.first - r.pos);
        tr.move(EPS);
        double dst = get_min_distance(tr).first;

        // cout << "pos = " << r.pos.x << " " << r.pos.y << " " << r.pos.z << "\n";
        // cout << "dd = " << r.pos.x - scene[0].center.x << " " << r.pos.y - scene[0].center.y << " " << r.pos.z - scene[0].center.z << "\n";
        // cout << "dd * d = " << (r.pos - scene[0].center) * r.dir << "\n";
        // cout << "dir = " << (x.first - r.pos).x << " " << (x.first - r.pos).y << " " << (x.first - r.pos).z << "\n";

        if (isnan(dst) || dst >= (x.first - r.pos).len()) {
            light += max(0.0, x.second * (norm * (x.first - r.pos)) / (x.first - r.pos).len());
            foo++;
        }
    }
    r.move(EPS);
    return scene[num].mat.color * (light + scene[num].mat.light) + trace(r, scene[num].mat.reflect * refl, deep + 1) * scene[num].mat.reflect;
}

int main() {
    int X = 2000, Y = 2000;
    BMP img;
    img.SetSize(X, Y);

    // BackGround
    // scene.push_back(Sphere(Point(0, 0, 0), 998, Material(Pixel(255, 255, 255), 0.8, 0.5)));

    // Scene
    scene.push_back(Sphere(Point(3.9, 1.15, -0.3), 1, Material(Pixel(0, 0, 100), 0.1, 0.5)));
    scene.push_back(Sphere(Point(4, -1.15, 0.3), 1, Material(Pixel(100, 0, 0), 0.6, 0)));
    // scene.push_back(Sphere(Point(0, -0.5, 0.3), 0.5, Material(Pixel(0, 100, 0), 0.1, 0.5)));
    // scene.push_back(Sphere(Point(100, 0, 0), 99, Material(Pixel(0, 0, 0), 0.7, 0)));
    // scene.push_back(Sphere(Point(-100, 0, 0), 99, Material(Pixel(0, 0, 0), 0.7, 0)));

    // scene.push_back(Sphere(Point(1.5, 1.7, 0), 1, Material(Pixel(0, 0, 100), 0.5, 0.5)));
    // scene.push_back(Sphere(Point(1.5, 0, 0), 0.2, Material(Pixel(255, 0, 0), 0, 0.5)));

    // Light
    // lights.push_back({Point(-1, 2, 10), 6});
    lights.push_back({Point(1.5, -1, -0.2), 6});
    lights.push_back({Point(4, 0, 0), 6});

    // Process
    int progress = 0;
    for (int i = 0; i < X; i++) {
        for (int j = 0; j < Y; j++) {
            Point d(1, (i - X / 2) / (X / 2.0), (j - Y / 2) / (Y / 2.0));

            img.SetPixel(i, j, trace(Ray(Point(0, 0, 0), d)).toBMPPixel(0.5));

            progress++;
            if ((progress - 1) * 100 / (X * Y) != progress * 100 / (X * Y)) {
                cout <<  progress * 100 / (X * Y) << "%" << endl;
            }
            // cout << i << " " << j << endl;
        }
    }

    img.WriteToFile("out.bmp");
    cout << "Completed!\n";
    return 0;
}


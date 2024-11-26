//
// Created by Varun Srinivasan on 24/11/2024.
//

#ifndef CMAKESFMLPROJECT_SCATTERBULLET_H
#define CMAKESFMLPROJECT_SCATTERBULLET_H

#endif //CMAKESFMLPROJECT_SCATTERBULLET_H

#include "Projectile.h"
#include <cmath>
#include <chrono>
#include <ctime>

class ScatterBullet : Projectile {
private:
    double x;
    double y;
    double angle_degrees;
    double angle;
    std::chrono::time_point<std::chrono::steady_clock> creation_time;

public:
    ScatterBullet(double x, double y, double angle) : x(x), y(y), creation_time(std::chrono::steady_clock::now()),
                                                      angle_degrees(angle) {
        to_rad(angle);
    }

    void to_rad(double ang) {
        angle = M_PI * ang / 180;
    }

    double get_x() { return x; }

    double get_y() { return y; }

    double get_angle() {
        return angle;
    }

    void set_x(double new_x) {
        x = new_x;
    }

    void set_y(double new_y) {
        y = new_y;
    }

    void set_angle(double angle) {
        to_rad(angle);
    }

    double get_elapsed_time() {
        auto now = std::chrono::steady_clock::now();
        return std::chrono::duration<double>(now - creation_time).count();
    }
};
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
    double angle;
    double x_vel;
    double y_vel;
    std::chrono::time_point<std::chrono::steady_clock> creation_time;

public:
    ScatterBullet(double x, double y, double angle) : x(x), y(y), creation_time(std::chrono::steady_clock::now()),
                                                      angle(angle) {
        x_vel = constants::BULLET_VELOCITY * cos(angle);
        y_vel = constants::BULLET_VELOCITY * sin(angle);
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

    double get_elapsed_time() {
        auto now = std::chrono::steady_clock::now();
        return std::chrono::duration<double>(now - creation_time).count();
    }

    void set_x_vel(double new_x_vel) {
        x_vel = new_x_vel;
    }

    void set_y_vel(double new_y_vel) {
        y_vel = new_y_vel;
    }

    double get_x_vel() {
        return x_vel;
    }

    double get_y_vel() {
        return y_vel;
    }
};
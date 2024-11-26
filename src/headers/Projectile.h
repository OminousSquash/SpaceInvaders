//
// Created by Varun Srinivasan on 30/10/2024.
//

#ifndef CMAKESFMLPROJECT_PROJECTILE_H
#define CMAKESFMLPROJECT_PROJECTILE_H


class Projectile {
private:
    bool terminated;
    int x;
    int y;

public:
    Projectile() : terminated(false) {}

    Projectile(int x, int y) : x(x), y(y), terminated(false) {}

    int get_x() {
        return x;
    }

    int get_y() {
        return y;
    }

    void set_x(int new_x) {
        x = new_x;
    }

    void set_y(int new_y) {
        y = new_y;
    }
};


#endif //CMAKESFMLPROJECT_PROJECTILE_H

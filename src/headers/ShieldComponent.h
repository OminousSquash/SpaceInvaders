//
// Created by Varun Srinivasan on 20/11/2024.
//

#ifndef CMAKESFMLPROJECT_SHIELDCOMPONENT_H
#define CMAKESFMLPROJECT_SHIELDCOMPONENT_H

#include <vector>


class ShieldComponent {
private:
    int x;
    int y;
    int height;
    bool display;
public:
    ShieldComponent(int x, int y, int height) : x(x), y(y), height(height), display(true) {}

    int get_x() {
        return x;
    }

    int get_y() {
        return y;
    }

    int get_height() {
        return height;
    }

    void kill_display() {
        display = false;
    }

    bool is_collidable() {
        return display;
    }
};

#endif //CMAKESFMLPROJECT_SHIELDCOMPONENT_H

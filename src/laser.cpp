#include "laser.hpp"
#include <iostream>

laser::laser(Vector2 position, int speed) {
    this->position = position;
    this->speed = speed;
    active = true;
}

void laser::draw() {
    if (active) {
        DrawRectangle(position.x, position.y, 4, 15, {255, 0, 0, 255});
    }
}

void laser::update() {
    position.y += speed;
    if (active) {
        if (position.y > GetScreenHeight() - 100 || position.y < 25) {
            active = false;
        }
    }
}

Rectangle laser::getrec() {
    Rectangle rec;
    rec.x = position.x;
    rec.y = position.y;
    rec.width = 4;
    rec.height = 15;
    return rec;
}
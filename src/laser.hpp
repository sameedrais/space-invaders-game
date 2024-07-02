#pragma once
#include<raylib.h>

class laser{
    private:
    Vector2 position;
    int speed;

    public:
    laser(Vector2 position,int speed);
    void update();
    void draw();
    Rectangle getrec();
    bool active;
};
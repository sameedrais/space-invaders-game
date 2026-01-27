#pragma once
#include<raylib.h>

class mysteryship{
    private:
    Vector2 position;
    Texture2D image;
    int speed;

    public:
    bool alive;
    mysteryship();
    ~mysteryship();
    void update();
    void draw();
    void spawn();
    Rectangle getrec();
};
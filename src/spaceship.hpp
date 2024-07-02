#pragma once
#include<raylib.h>
#include"laser.hpp"
#include<vector>

class spaceship{
    private:
    Texture2D image;
    Vector2 position;
    double lastfiretime;
    Sound lasersound;

    public:
    std::vector<laser> lasers;
    spaceship();
    ~spaceship();
    void moveleft();
    void moveright();
    void draw();
    void firelaser();
    Rectangle getrec();
    void reset();
};
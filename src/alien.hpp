#pragma once
#include<raylib.h>

class alien{
    public:
    int type;
    Vector2 position;
    static Texture2D alienimages[3];
    alien(int type,Vector2 position);
    void update(int direction);
    void draw();
    int gettype();
    static void unloadimages();
    Rectangle getrect();
};
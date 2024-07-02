#include "mysteryship.hpp"

mysteryship::mysteryship() {
    image=LoadTexture("graphics/alienspaceship.png");
    alive=false;
}

mysteryship::~mysteryship() {
    UnloadTexture(image);
}

void mysteryship::update() {
    if(alive){
        position.x+=speed;
        if(position.x>GetScreenWidth()-image.width-25||position.x<25){
            alive=false;
        }
    }
}

void mysteryship::draw() {
    if(alive){
        DrawTextureV(image,position,WHITE);
    }
}

void mysteryship::spawn() {
    position.y=90;
    int side=GetRandomValue(0,1);
    if(side==0){
        position.x=25;
        speed=3;
    } else {
        position.x=GetScreenWidth()-image.width-25;
        speed=-3;
    }
    alive=true;
}

Rectangle mysteryship::getrec() {
    if(alive){
        return{position.x,position.y,float(image.width),float(image.height)};
    } else {
        return{position.x,position.y,0,0};
    }
}
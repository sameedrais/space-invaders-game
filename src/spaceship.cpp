#include "spaceship.hpp"

spaceship::spaceship(){
    image=LoadTexture("graphics/a.png");
    position.x=(GetScreenWidth()-image.width)/2;
    position.y=GetScreenHeight()-image.height-100;
    lastfiretime=0.0;
    lasersound=LoadSound("sounds/laser.mp3");
}

spaceship::~spaceship() {
    UnloadTexture(image);
    UnloadSound(lasersound);
}

void spaceship::draw() {
    DrawTextureV(image,position,WHITE);
}

void spaceship::moveleft() {
    position.x-=7;
    if(position.x<25) {
        position.x=25;
    }
}

void spaceship::moveright() {
    position.x+=7;
    if(position.x>GetScreenWidth()-image.width-25){
        position.x=GetScreenWidth()-image.width-25;

    }
}

void spaceship::firelaser() {
    if(GetTime()-lastfiretime>=0.35){
    lasers.push_back(laser({position.x+image.width/2-2,position.y},-6));
    lastfiretime=GetTime();
    PlaySound(lasersound);
    }
}

Rectangle spaceship::getrec() {
    return {position.x,position.y,float(image.width),float(image.height)};
}

void spaceship::reset() {
    position.x=(GetScreenWidth()-image.width)/2.0f;
    position.y=GetScreenHeight()-image.height-100;
    lasers.clear();
}

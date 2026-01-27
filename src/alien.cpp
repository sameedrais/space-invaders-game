#include "alien.hpp"

Texture2D alien::alienimages[3]={};

alien::alien(int type, Vector2 position) {
    this->type=type;
    this->position=position;
    if(alienimages[type-1].id==0){    
        switch(type){
            case 1:
            alienimages[0]=LoadTexture("graphics/jadu.png");
            break;
            case 2:
            alienimages[1]=LoadTexture("graphics/jadu2.png");
            break;
            case 3:
            alienimages[2]=LoadTexture("graphics/alien_3.png");
            break;
            default:
            alienimages[0]=LoadTexture("graphics/jadu.png");
            break;
            
        }
    }
}

void alien::draw() {
    DrawTextureV(alienimages[type-1],position,WHITE);
}

int alien::gettype() {
    return type;
}

void alien::unloadimages() {
    for(int i=0;i<4;i++){
        UnloadTexture(alienimages[i]);
    }
}

Rectangle alien::getrect() {
    return {position.x,position.y,float(alienimages[type-1].width),float(alienimages[type-1].height)};
}

void alien::update(int direction) {
    position.x+=direction;
}

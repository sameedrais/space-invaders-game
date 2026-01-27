#include "block.hpp"

Block::Block(Vector2 position) {
    this->position=position;
}

void Block::draw() {
    DrawRectangle(position.x,position.y,3,3,{0,0,255,255});
}

Rectangle Block::getrec() {
    Rectangle rec;
    rec.x=position.x;
    rec.y=position.y;
    rec.width=3;
    rec.height=3;
    return rec;
}

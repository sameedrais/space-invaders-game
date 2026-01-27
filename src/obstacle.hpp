#pragma once
#include<vector>
#include"block.hpp"

class obstacle {
    public:
    Vector2 position;
    std::vector<Block>blocks;
    static std::vector<std::vector<int>> grid;
    obstacle(Vector2 position);
    void draw();
};
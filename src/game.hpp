#pragma once
#include<raylib.h>
#include"spaceship.hpp"
#include"obstacle.hpp"
#include"alien.hpp"
#include"mysteryship.hpp"

class game{
    private:
    spaceship s;
    mysteryship m;
    std::vector<obstacle> obstacles;
    std::vector<alien> aliens;
    std::vector<laser> alienlaser;
    int aliensdirection;
    constexpr static float alienlasershootinterval = 0.35;
    float lasttimealienfired;
    float mysteryshipspawninterval;
    float timelastspawn;
    Sound explotionsound;
    void initgame();
    void reset();
    std::vector<obstacle> createobstacles();
    std::vector<alien> createaliens();
    void deleteinactivelaser();
    void movealiens();
    void movedownaliens(int distance);
    void alienshootlaser();
    void checkforcollision();
    int loadhighscorefromfile();
    void savehighscoretofile(int highscore);
    void checkforhighscore();
    void GameOver();

    public:
    bool run;
    int lives;
    int score;
    int highscore;
    Music music;
    game();
    ~game();
    void draw();
    void update();
    void handleinput();
};

#include "game.hpp"
#include<iostream>
#include<fstream>


game::game() {
    music=LoadMusicStream("sounds/background.mp3");
    PlayMusicStream(music);
    explotionsound=LoadSound("sounds/explosion.mp3");
    
    initgame();
}

game::~game() {
    alien::unloadimages();
    UnloadMusicStream(music);
    UnloadSound(explotionsound);
}

void::game::update() {
    if(run){
        double currenttime=GetTime();
        if(currenttime-timelastspawn>mysteryshipspawninterval){
            m.spawn();
            timelastspawn=GetTime();
            mysteryshipspawninterval=GetRandomValue(10,20);
        }
        for(auto& laser:s.lasers){
            laser.update();
        }
        movealiens();
        alienshootlaser();
        for(auto& laser:alienlaser){
            laser.update();
        }
        deleteinactivelaser();
        m.update();
        checkforcollision();
    }
    else{
        if(IsKeyDown(KEY_ENTER)){
            reset();
            initgame();
        }
    }
    
}

void game::draw() {
    s.draw();
    for(auto& laser:s.lasers){
        laser.draw();
    }
    for(auto& obstacle:obstacles){
        obstacle.draw();
    }
    for(auto& alien:aliens){
        alien.draw();
    }
    for(auto& laser:alienlaser){
        laser.draw();
    }
    m.draw();
}

void game::handleinput() {
    if(run){
        if(IsKeyDown(KEY_LEFT)){
            s.moveleft();
        }
        else if(IsKeyDown(KEY_RIGHT)){
            s.moveright();
        }
        else if(IsKeyDown(KEY_SPACE)){
            s.firelaser();
        }
    }
}

void game::initgame() {
    obstacles=createobstacles();
    aliens=createaliens();
    aliensdirection=1;
    lasttimealienfired=0.0;
    m.spawn();
    timelastspawn=0.0;
    mysteryshipspawninterval=GetRandomValue(10,20);
    lives=3;
    score=0;
    highscore=loadhighscorefromfile();
    run=true;
}

void game::reset() {
    s.reset();
    aliens.clear();
    alienlaser.clear();
    obstacles.clear();
}

void game::deleteinactivelaser() {
    for(auto it=s.lasers.begin();it!=s.lasers.end();){
        if(!it->active){
            it=s.lasers.erase(it);
        }
        else{
            ++it;
        }
    }
     for(auto it=alienlaser.begin();it!=alienlaser.end();){
        if(!it->active){
            it=alienlaser.erase(it);
        }
        else{
            ++it;
        }
    }
}

void game::movedownaliens(int distance) {
    for(auto& alien:aliens){
        alien.position.y+=distance;
    }
}

void game::checkforcollision() {
    //spaceship laser
    for(auto& laser:s.lasers){
        auto it=aliens.begin();
        while(it!=aliens.end()){
            if(CheckCollisionRecs(it->getrect(),laser.getrec())){
                PlaySound(explotionsound);
                if(it->type==1){
                    score+=100;
                }
                else if(it->type==2){
                    score+=200;
                }
                else if(it->type==3){
                    score+=300;
                }
                checkforhighscore();
                it=aliens.erase(it);
                laser.active=false;
            }
            else{
                ++it;
            }
        };
        for(auto& obstacle:obstacles){
            auto it=obstacle.blocks.begin();
            while(it!=obstacle.blocks.end()){
                if(CheckCollisionRecs(it->getrec(),laser.getrec())){
                    it=obstacle.blocks.erase(it);
                    laser.active=false;
                }
                else{
                    ++it;
                }
            }
        }
        if(CheckCollisionRecs(m.getrec(),laser.getrec())){
            m.alive=false;
            laser.active=false;
            score+=500;
            checkforhighscore();
            PlaySound(explotionsound);
        }
    }
    //Alien lasers
    for(auto& laser:alienlaser){
        if(CheckCollisionRecs(laser.getrec(),s.getrec())){
            laser.active=false;
            lives--;
            if(lives==0){
                GameOver();
            }
        }
        for(auto& obstacle:obstacles){
            auto it=obstacle.blocks.begin();
            while(it!=obstacle.blocks.end()){
                if(CheckCollisionRecs(it->getrec(),laser.getrec())){
                    it=obstacle.blocks.erase(it);
                    laser.active=false;
                }
                else{
                    ++it;
                }
            }
        }
    }
    //Alien collision with obstacle:
    for(auto& alien:aliens){
        for(auto& obstacle:obstacles){
            auto it=obstacle.blocks.begin();
            while(it!=obstacle.blocks.end()){
                if(CheckCollisionRecs(it->getrec(),alien.getrect())){
                    it=obstacle.blocks.erase(it);
                }
                else{
                    it++;
                }
            }
        }
        if(CheckCollisionRecs(alien.getrect(),s.getrec())){
            GameOver();

        }
    }

    
}

std::vector<obstacle> game::createobstacles() {

   int obstaclewidth=obstacle::grid[0].size()*3;
   float gap=(GetScreenWidth()-(4*obstaclewidth))/5;
   for(int i=0;i<4;i++){
    float offsetx=(i+1)*gap+i*obstaclewidth;
    obstacles.push_back(obstacle({offsetx,float(GetScreenHeight()-200)}));
   }
   return obstacles;
}

std::vector<alien> game::createaliens() {

    std::vector<alien>aliens;
    for(int row=0;row<5;row++){
        for(int column=0;column<11;column++){
            int alientype;
            if(row==0){
                alientype=3;

            }
            else if(row==1||row==2){
                alientype=2;
            }
            else{
                alientype=1;
            }
            float x=75+column*55;
            float y=110+row*55;
            aliens.push_back(alien(alientype, {x,y}));
        }

    }
    return aliens;
}

void game::movealiens() {
    for(auto& alien:aliens){
        if(alien.position.x+alien.alienimages[alien.type-1].width>GetScreenWidth()-25){
            aliensdirection=-1;
            movedownaliens(4);
        }
        if(alien.position.x<25){
            aliensdirection=1;
            movedownaliens(4);
        }
        alien.update(aliensdirection);

    }
}

void game::alienshootlaser() {
    double currenttime=GetTime();
    if(currenttime-lasttimealienfired>=alienlasershootinterval&&!aliens.empty()){
        int randomindex=GetRandomValue(0,aliens.size()-1);
        alien& a=aliens[randomindex];
        alienlaser.push_back(laser({a.position.x+a.alienimages[a.type-1].width/2,a.position.y+a.alienimages[a.type-1].height},6));
        lasttimealienfired=GetTime();
    }
}

void game::GameOver() {
    run=false;
}

void game::checkforhighscore() {
    if(score>highscore){
        highscore=score;
        savehighscoretofile(highscore);
    }
}

void game::savehighscoretofile(int highscore) {
    std::ofstream highscorefile("highscore.txt");
    if(highscorefile.is_open()){
        highscorefile<<highscore;
        highscorefile.close();
    }
    else{
        std::cerr<<"Failed to save highscore to file"<<std::endl;
    }
}

int game::loadhighscorefromfile() {
    int loadedhighscore=0;
    std::ifstream highscorefile("highscore.txt");
    if(highscorefile.is_open()){
        highscorefile>>loadedhighscore;
        highscorefile.close();
    }
    else{
        std::cerr<<"failed to load from high score file"<<std::endl;
    }
    return loadedhighscore;
}

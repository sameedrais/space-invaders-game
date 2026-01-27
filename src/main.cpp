#include<string>
#include <raylib.h>
#include"game.hpp"
#include"laser.hpp"

std::string formatwithleadingzeros(int number,int width){
    std::string numbertext=std::to_string(number);
        int leadingzeros=width-numbertext.length();
       return  numbertext=std::string(leadingzeros,'0')+numbertext;
}

int main()
{
    Color grey={29,29,27,255};
    Color blue={0,0,255,255};
    
    int offset=50;
    int windowheight=700;
    int windowwidth=750;
    InitWindow(windowwidth+offset,windowheight+2*offset,"SPACE SHOOTER");
    InitAudioDevice();
    Font font=LoadFontEx("font/monogram.ttf",64,0,0);
    Texture2D spaceshipimage=LoadTexture("graphics/a.png");
    SetTargetFPS(60);
    game g;
   
    
    
    
    while(WindowShouldClose() == false) {
        UpdateMusicStream(g.music);
        g.handleinput();
        g.update();
        
        BeginDrawing();
        ClearBackground(grey);
        DrawRectangleRoundedLines({10,10,780,780},0.18f,20,2,blue);
        DrawLineEx({25,730},{775,730},3,blue);
        if(g.run) {
            DrawTextEx(font,"LEVEL 01",{570,740},34,2,blue);

        } else {
            DrawTextEx(font,"GAMEOVER",{570,740},34,2,blue);
        }
        float x=50.0;
        for(int i=0;i<g.lives;i++){
            DrawTextureV(spaceshipimage,{x,745},WHITE);
            x+=50;
        }

        DrawTextEx(font,"SCORE",{50,15},34,2,blue);
        std::string scoretext=formatwithleadingzeros(g.score,5);
        DrawTextEx(font,scoretext.c_str(),{50,40},34,2,blue);
        DrawTextEx(font,"HIGH-SCORE",{570,15},34,2,blue); 
        std::string highscoretext=formatwithleadingzeros(g.highscore,5);
        DrawTextEx(font,highscoretext.c_str(),{655,40},34,2,blue);
        
        g.draw();
        EndDrawing();

    }

    CloseWindow();
    CloseAudioDevice();
    UnloadFont(font);
    UnloadTexture(spaceshipimage);

    return 0;
}
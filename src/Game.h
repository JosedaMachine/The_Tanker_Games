#ifndef GAME_H_
#define GAME_H_

#include <vector>

#include <SDL2/SDL.h>

#include "macros.h"

class GameObject;
class SDL_Renderer;

class Game{
public:
     Game();
     virtual ~Game();
     
     void init(int w, int h);
     void run();

private:

    std::vector<GameObject*> objs_;
    SDL_Renderer* rend;
    SDL_Window* win;
    SDL_Texture* tex;
    int speed, close;
    int width_, height_;
    SDL_Rect dest;
};
#endif
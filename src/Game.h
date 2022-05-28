#ifndef GAME_H_
#define GAME_H_

#include <vector>

#include <SDL2/SDL.h>

#include "macros.h"

class GameObject;
class SDL_Renderer;

class Game
{
public:
    Game();
    virtual ~Game();

    void init(int w, int h);
    void run();
    void shutdown();

    void refresh();

private:
    std::vector<GameObject *> objs_;
};
#endif
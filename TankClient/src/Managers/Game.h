#ifndef GAME_H_
#define GAME_H_

#include <vector>

#include <SDL2/SDL.h>

#include "../Utils/macros.h"
#include "../Utils/Environment.h"
#include "../Net/Socket.h"

class GameObject;
class SDL_Renderer;

class Game
{
public:
    Game(const char * ip, const char * p);
    virtual ~Game();

    void init(int w, int h);
    void run();
    void shutdown();

    void refresh();

private:
    std::vector<GameObject *> objs_;
    // Socket socket_client;
};
#endif
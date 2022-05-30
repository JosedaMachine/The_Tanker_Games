#ifndef GAME_H_
#define GAME_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include "../Net/Socket.h"
#include "../Utils/TankMessageClient.h"

#include <unistd.h>
#include <string>
#include <algorithm>
#include <vector>

class GameObject;
class SDL_Renderer;
class Tank;

class App {
public:
    App(const char * s, const char * p);
    virtual ~App();

    void init(int w, int h);
    void run();
    void shutdown();

    void refresh();
    void sendMatchMessage(TankMessageClient::ClientMessageType msg);
private:
    std::vector<GameObject *> objs_;
    Socket client_socket;

    Tank* player_1, *player_2;
};
#endif
#ifndef GAME_H_
#define GAME_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <thread>

#include "../Net/Socket.h"

#include "../Utils/TankMessageClient.h"
#include "../Utils/TankMessageServer.h"

#include "../Utils/Vector2D.h"

class GameObject;
class SDL_Renderer;
class Tank;
class Bullet;

struct InitData {
    Vector2D pos;
    Vector2D dim;
    float rot;
};

class App {
public:
    App(const char * s, const char * p);
    virtual ~App();

    void init(int w, int h);
    void run();
    void refresh();
    void shutdown();
    void initConnection();
    void netMessage_thread();
    void sendGameMessage(TankMessageClient::InputType input);
    void sendMatchMessage(TankMessageClient::ClientMessageType msg, InitData* data = nullptr);
    std::vector<GameObject *>* getGOsReference();
    void updateGOsInfo(TankMessageServer* msg);
private:
    std::vector<GameObject *> objs_;
    Socket client_socket;
    Tank* player_1, *player_2;
    Bullet* bullet;
};
#endif
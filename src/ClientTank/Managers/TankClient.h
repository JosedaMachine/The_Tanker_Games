#ifndef TANKCLIENT_H_
#define TANKCLIENT_H_

#include <unistd.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <thread>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include "../../Utils/Socket.h"

#include "../../Utils/TankMessageClient.h"
#include "../../Utils/TankMessageServer.h"

#include "../../Utils/Vector2D.h"

#define TANK_SIZE 90

class GameObject;
class SDL_Renderer;
class Tank;
class Bullet;

struct InitData
{
    Vector2D dim;
    float rot;
};

class TankClient
{
public:
    TankClient(const char *s, const char *p);
    virtual ~TankClient();

    void init(int w, int h);
    void run();
    void shutdown();

    std::vector<GameObject *> *getGOsReference()
    {
        return &objs_;
    };

    void sendGameMessage(TankMessageClient::InputType input);
    void sendMatchMessage(TankMessageClient::ClientMessageType msg, InitData *data = nullptr);

private:
    Socket client_socket;

    std::vector<GameObject *> objs_;
    std::vector<GameObject *> gObjsToAdd_;

    Tank *player_1, *player_2;
    Bullet *bullet_1, *bullet_2;

    bool tank_1_won;

    TankMessageServer::ServerState currentState, nextState;

    void net_message_thread();

    void checkState();
    void changeState(const TankMessageServer::ServerState state);
    void loadScreen(const std::string &textFile, const std::string &fontFile, const std::string &text,
                    const Vector2D &textPos, const Vector2D &textDim, const SDL_Color &color, const int &size);
    void playLoad();

    void refresh();

    void shoot(Bullet *&bullet, const Vector2D &pos, const Vector2D &dim);
    void removeBullet(Bullet *&bullet);

    void updateGOsInfo(TankMessageServer *msg);

    void clearGameObjects();
};
#endif
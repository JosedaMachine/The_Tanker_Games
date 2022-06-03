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

    // main methods for game loop: initialization, run and shutdown
    void init(int w, int h); 
    void run();
    void shutdown();

    // send message to server
    void sendGameMessage(TankMessageClient::InputType input);
    void sendMatchMessage(TankMessageClient::ClientMessageType msg, InitData *data = nullptr);

    inline std::vector<GameObject *> *getGOsReference()
    {
        return &objs_;
    };

private:
    // socket
    Socket client_socket;

    // general game objects vector for loop
    std::vector<GameObject *> objs_;
    std::vector<GameObject *> gObjsToAdd_;

    // specific game objects needed to make some message handling faster
    Tank *player_1, *player_2;
    Bullet *bullet_1, *bullet_2;

    // game state
    TankMessageServer::ServerState currentState, nextState;
    bool tank_1_won;

    // message thread
    void client_message_thread();

    // update gOs according to data received from a message
    void updateGOsInfo(TankMessageServer *msg);

    // auxiliary methods to create and destroy bullets
    void shoot(Bullet *&bullet, const Vector2D &pos, const Vector2D &dim);
    void removeBullet(Bullet *&bullet);

    // check & change gOs according to new game state
    void checkState();
    void changeState(const TankMessageServer::ServerState state);
    void loadScreen(const std::string &textFile, const std::string &fontFile, const std::string &text,
                    const Vector2D &textPos, const Vector2D &textDim, const SDL_Color &color, const int &size);
    void playLoad();

    void refresh(); // cleans gOs if they are disabled
    void clearGameObjects(); // clears all gOs
};
#endif
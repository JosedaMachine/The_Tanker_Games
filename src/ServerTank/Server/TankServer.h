#include <unistd.h>
#include <string>
#include <mutex>

#include "../../Utils/Socket.h"
#include "../../Utils/TankMessageClient.h"
#include "../../Utils/TankMessageServer.h"

#include "../../Utils/Vector2D.h"

#define TICK_RATE 16666 // microseconds

#define BULLET_SIZE 10

class TankServer {
public:
    TankServer(const char * s, const char * p);

    // net messages handler
    void game_thread();
    
    // main game loop
    void run();

private:
    Socket server_socket;
    Socket* tank_1, *tank_2;

    std::mutex input_mutex;

    TankMessageClient::InputType input_t1, input_t2;

    int win_width, win_height;

    Vector2D pos_t1, pos_t2;
    Vector2D dim_t1, dim_t2;
    Vector2D vel_t1, vel_t2;
    float rot_t1, rot_t2;

    bool shoot;

    Vector2D pos_b;
    Vector2D dim_b;
    Vector2D vel_b;

    void init();

    void saveInput(Socket* player_sock, TankMessageClient::InputType input);
    void handleInput();

    bool addPlayer(Socket* player_sock, int& pl);
    void removePlayer(Socket* player_sock);

    void initPlayer(const int& pl, const TankMessageClient* msg);

    void stepSimulation();
    void updateInfoClients();

    bool outOfBounds(const Vector2D pos, Vector2D& dim);
    void checkCollisions();
};
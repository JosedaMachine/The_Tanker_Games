#include <unistd.h>
#include <string>
#include <mutex>
#include <vector>

#include "../../Utils/Socket.h"
#include "../../Utils/TankMessageClient.h"
#include "../../Utils/TankMessageServer.h"

#include "../../Utils/Vector2D.h"

#define TICK_RATE 16666 // microseconds
#define BULLET_SIZE 10
#define GAME_OVER_TIME 2000

struct Obstacle {
    Vector2D pos;
    Vector2D dim;
};

class TankServer {
public:
    TankServer(const char * s, const char * p);

    // net messages handler
    void server_message_thread();
    
    // main game loop
    void run();

private:
    // sockets
    Socket server_socket;
    Socket* tank_1, *tank_2;

    std::mutex input_mutex; // mutex lock to handle input safely

    // server stae
    TankMessageServer::ServerState state;
    bool t1_ready, t2_ready;

    int timer; // game over timer

    TankMessageClient::InputType input_t1, input_t2; 
    
    // game data
    int win_widthL, win_heightT;
    int win_width, win_height;

    Vector2D pos_t1, pos_t2;
    Vector2D dim_t1, dim_t2;
    Vector2D vel_t1, vel_t2;
    float rot_t1, rot_t2;

    bool shoot_t1, shoot_t2;
    Vector2D pos_b1, pos_b2;
    Vector2D dim_b;
    Vector2D vel_b1, vel_b2;

    int life_t1, life_t2;

    std::vector<Obstacle> obstacles_;

    // reset to default values
    void reset();

    // save & handle input
    void saveInput(Socket* player_sock, TankMessageClient::InputType input);
    void handleInput();

    // add & remove player from server data
    bool addPlayer(Socket* player_sock, int& pl);
    void removePlayer(Socket* player_sock);
    void initPlayer(const int& pl, const TankMessageClient* msg);

    // update loop simulation
    void stepSimulation();

    // physics methods for update simulation
    void checkCollisions();
    bool outOfBounds(const Vector2D pos, Vector2D& dim);
    bool outOfBounds(const Vector2D pos, Vector2D& dim, const Vector2D& limit1, const Vector2D& limit);

    // update data to players
    void updateInfoClients();

    // update server state to players
    void sendStateMessage();

    // creates obstacles upon playing state
    void createObstacles();
};
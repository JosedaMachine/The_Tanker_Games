#include <unistd.h>
#include <string>
#include <mutex>

#include "../Net/Socket.h"
#include "../Utils/TankMessageClient.h"
#include "../Utils/TankMessageServer.h"


#include "../Utils/Vector2D.h"

#define TICK_RATE 16666 // microseconds

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

    Vector2D pos_t1, pos_t2;
    Vector2D vel_t1, vel_t2;
    float rot_t1, rot_t2;

    void setup();

    void saveInput(Socket* player_sock, TankMessageClient::InputType input);
    void handleInput();

    void addPlayer(Socket* player_sock);
    void removePlayer(Socket* player_sock);

    void stepSimulation();
};
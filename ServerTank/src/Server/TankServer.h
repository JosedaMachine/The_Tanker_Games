#include <unistd.h>
#include <string.h>
#include <string>
#include <cctype>
#include <algorithm>
#include <vector>
#include <memory>

#include "../Net/Socket.h"

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

    void addPlayer(Socket* player_sock);
    void removePlayer(Socket* player_sock);
};
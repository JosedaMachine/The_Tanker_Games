#include "Server/TankServer.h"
#include <iostream>

int main(int argc, char **argv) {
    if(argc < 3){
        std::cout << "Usage-> ./Server_TankerGames.out <ip>(0.0.0.0) <port>(2000)\n";
        return 0;
    }

    TankServer server(argv[1], argv[2]);

    server.start();

    return 0;
}
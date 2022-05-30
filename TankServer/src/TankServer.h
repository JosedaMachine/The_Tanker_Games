#include <unistd.h>
#include <string.h>
#include <string>
#include <cctype>
#include <algorithm>
#include <vector>
#include <memory>

#include "Serializable.h"
#include "Socket.h"

#define NICK_SIZE sizeof(char) * 8
#define MESSAGE_DATA_SIZE sizeof(char) * 80

#define MESSAGE_SIZE NICK_SIZE + MESSAGE_DATA_SIZE + sizeof(uint8_t)

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

/**
 *  Mensaje del protocolo de la aplicación de Chat
 *
 *  +-------------------+
 *  | Tipo: uint8_t     | 0 (login), 1 (mensaje), 2 (logout)
 *  +-------------------+
 *  | Nick: char[8]     | Nick incluido el char terminación de cadena '\0'
 *  +-------------------+
 *  |                   |
 *  | Mensaje: char[80] | Mensaje incluido el char terminación de cadena '\0'
 *  |                   |
 *  +-------------------+
 *
 */
class TankServer {
public:
    TankServer(const char * s, const char * p);
    void start();

    void searchingPlayers();
    void waitForPlayer(Socket* tank);

private:
    std::vector<std::unique_ptr<Socket>> clients;

    Socket server_socket;
    Socket* tank_1, *tank_2;
};
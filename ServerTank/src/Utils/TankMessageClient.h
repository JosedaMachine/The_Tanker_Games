#include <unistd.h>
#include <string.h>
#include <string>
#include <cctype>

#include "../Net/Serializable.h"

#define CLIENT_MESSAGE_SIZE sizeof(ClientMessageType) + sizeof(InputType)

class TankMessageClient: public Serializable
{
public:
    enum ClientMessageType : uint8_t {
        REGISTER = 0,
        HANDLE_INPUT = 1,
        QUIT = 2
    };

    enum InputType : uint8_t {
        NONE = 0,
        LEFT = 1,
        RIGHT = 2,
        FRONT = 3,
        BACK = 4, 
        SHOOT = 5,
        PLAY = 6,
        ESCAPE = 7
    };

    TankMessageClient() {};

    TankMessageClient(const ClientMessageType& t, const InputType& i) : type(t), input(i) {};

    void to_bin();

    int from_bin(char* bobj);

public:
    ClientMessageType type;
    InputType input;
};
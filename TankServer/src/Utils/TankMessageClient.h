#include <unistd.h>
#include <string.h>
#include <string>
#include <cctype>

#include "../Net/Serializable.h"

class TankMessageClient: public Serializable
{
public:
    enum MessageType{
        LEFT   = 0,
        RIGHT = 1,
        DOWN  = 2,
        UP  = 3,
        SHOOT  = 4,
        REGISTER = 5,
        LOGOUT  = 6
    };

    TankMessageClient() {};

    TankMessageClient(const std::string& n, const std::string& m) : nick(n), message(m) {};

    void to_bin();

    int from_bin(char* bobj);

public:
    uint8_t type;

    std::string nick;
    std::string message;
};
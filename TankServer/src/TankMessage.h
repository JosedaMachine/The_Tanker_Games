#include <unistd.h>
#include <string.h>
#include <string>
#include <cctype>

#include "Serializable.h"

class TankMessage: public Serializable
{
public:
    enum MessageType{
        REGISTER   = 0,
        MESSAGE = 1,
        LOGOUT  = 2
    };

    TankMessage() {};

    TankMessage(const std::string& n, const std::string& m) : nick(n), message(m) {};

    void to_bin();

    int from_bin(char* bobj);

public:
    uint8_t type;

    std::string nick;
    std::string message;
};
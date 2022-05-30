#include <unistd.h>
#include <string>
#include <cctype>

#include "Serializable.h"

class TankMessageClient : public Serializable
{
public:
    enum MessageType {
        REGISTER = 0,
        HANDLE_INPUT = 1,
        QUIT = 2
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
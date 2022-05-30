#include <unistd.h>
#include <string.h>
#include <string>
#include <cctype>

#include "../Net/Serializable.h"

class TankMessageServer: public Serializable
{
public:
    TankMessageServer() {};

    TankMessageServer(const std::string& n, const std::string& m) : nick(n), message(m) {};

    void to_bin();

    int from_bin(char* bobj);

public:
    uint8_t type;

    std::string nick;
    std::string message;
};
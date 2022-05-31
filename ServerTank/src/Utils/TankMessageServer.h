#include <unistd.h>
#include <string.h>
#include <string>
#include <cctype>

#include "../Net/Serializable.h"

#include "../Utils/Vector2D.h"

#define SERVER_MESSAGE_SIZE 4 * sizeof(Vector2D) + 2 * sizeof(float)

class TankMessageServer: public Serializable
{
public:
    enum ServerMessageType : uint8_t {
        REGISTER = 0,
        HANDLE_INPUT = 1,
        QUIT = 2
    };

    enum ActionType : uint8_t {
        NONE = 0,
        CREATE_BULLET = 1,
        CREATE_OBSTACLE = 2,
        FRONT = 3,
        BACK = 4, 
        SHOOT = 5,
        PLAY = 6,
        ESCAPE = 7
    };

    TankMessageServer() {};

    TankMessageServer(const Vector2D& p_t1, const Vector2D& p_t2, const float& r_t1, const float& r_t2) 
                : pos_t1(p_t1), pos_t2(p_t2), rot_t1(r_t1), rot_t2(r_t2) {};

    void to_bin();

    int from_bin(char* bobj);

public:

    Vector2D pos_t1, pos_t2, dim_t1, dim_t2 ;
    float rot_t1, rot_t2;
};
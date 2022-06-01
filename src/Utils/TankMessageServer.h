#include <unistd.h>
#include <string.h>
#include <string>
#include <cctype>

#include "Serializable.h"
#include "Vector2D.h"

#define SERVER_MESSAGE_SIZE sizeof(ServerMessageType) + sizeof(ActionType) + 4 * sizeof(Vector2D) + 2 * sizeof(float) + sizeof(bool)

class TankMessageServer: public Serializable
{
public:
    enum ServerMessageType : uint8_t {
        UPDATE_INFO = 0,
        ACTION = 1,
    };

    enum ActionType : uint8_t {
        NONE = 0,
        CREATE_BULLET = 1,
        CREATE_OBSTACLE = 2,
        DESTROY_BULLET = 3,
    };

    TankMessageServer() {};

    TankMessageServer(const Vector2D& pos_b, const Vector2D& dim_b) : pos_bullet(pos_b), dim_bullet(dim_b) {};

    TankMessageServer(const Vector2D& p_t1, const Vector2D& p_t2, const float& r_t1, const float& r_t2, const bool& s, const Vector2D& p_b) 
                : pos_t1(p_t1), pos_t2(p_t2), rot_t1(r_t1), rot_t2(r_t2), shoot(s), pos_bullet(p_b) {};

    void to_bin();

    int from_bin(char* bobj);

public:

    ServerMessageType type;
    ActionType action_;

    Vector2D pos_t1, pos_t2;
    float rot_t1, rot_t2;

    bool shoot;
    Vector2D pos_bullet, dim_bullet;
};
#include <unistd.h>
#include <string.h>
#include <string>
#include <cctype>

#include "Serializable.h"
#include "Vector2D.h"

#define SERVER_MESSAGE_SIZE sizeof(ServerMessageType) + sizeof(ActionType) + 5 * sizeof(Vector2D) + 2 * sizeof(float) + sizeof(bool)*2 + sizeof(ServerState) + sizeof(int)

class TankMessageServer: public Serializable
{
public:
    enum ServerMessageType : uint8_t {
        UPDATE_STATE = 0,
        UPDATE_INFO = 1,
        ACTION = 2
    };

    enum ServerState : uint8_t {
        WAITING = 0,
        READY = 1,
        PLAYING = 2,
        GAME_OVER = 3,
        SERVER_QUIT = 4,
        EMPTY = 6
    };

    enum ActionType : uint8_t {
        NONE = 0,
        CREATE_OBSTACLE = 1,
        CREATE_BULLET_1 = 2,
        CREATE_BULLET_2 = 3,
        DESTROY_BULLET_1 = 4,
        DESTROY_BULLET_2 = 5,
        DAMAGE_1 = 6,
        DAMAGE_2 = 7,
    };

    TankMessageServer() {};

    TankMessageServer(int life_) : life(life_) {};

    TankMessageServer(const ServerState s) : state(s) {};

    TankMessageServer(const Vector2D& pos_b, const Vector2D& dim_b) : pos_bullet_1(pos_b), dim_bullet(dim_b) {};

    TankMessageServer(const Vector2D& p_t1, const Vector2D& p_t2, const float& r_t1, const float& r_t2, const bool& s, const Vector2D& p_b1, const Vector2D& p_b2) 
                : pos_t1(p_t1), pos_t2(p_t2), rot_t1(r_t1), rot_t2(r_t2), shoot(s), pos_bullet_1(p_b1), pos_bullet_2(p_b2) {};

    void to_bin();

    int from_bin(char* bobj);

public:

    ServerMessageType type;
    ActionType action_;

    Vector2D pos_t1, pos_t2;
    float rot_t1, rot_t2;

    bool shoot;
    Vector2D pos_bullet_1, pos_bullet_2, dim_bullet;

    int life;

    bool playerOneHasWon;
    ServerState state;
};
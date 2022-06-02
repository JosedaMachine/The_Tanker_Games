#include <unistd.h>
#include <string.h>
#include <string>
#include <cctype>

#include "Serializable.h"
#include "Vector2D.h"

#define CLIENT_MESSAGE_SIZE sizeof(ClientMessageType) + sizeof(InputType) + (4 * sizeof(int)) + sizeof(float) + (2 * sizeof(Vector2D))

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

    TankMessageClient(const ClientMessageType& t, const InputType& i)
        : type(t), input(i), win_widthL(0), win_width(0), win_heightT(0), win_height(0), dim(), rot(0) {};

    void setDefaultValues(const int &w_w, const int &w_h, const Vector2D &d, const float &r);

    void setDefaultValues(const int &w_wL, const int &w_w, const int &w_hT, const int &w_h, const Vector2D &d, const float &r);

    void to_bin();

    int from_bin(char* bobj);

public:
    ClientMessageType type;

    // input value for HANDLE_INPUT
    InputType input;

    // initial values for REGISTER message
    int win_widthL, win_width, win_heightT, win_height;

    Vector2D dim;
    float rot;
};
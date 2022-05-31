#include "TankMessageClient.h"

void TankMessageClient::setDefaultValues(const int &w_w, const int &w_h, const Vector2D &p, const Vector2D &d, const float &r)
{
    win_width = w_w; win_height = w_h;
    pos = p; dim = d; rot = r;
};

void TankMessageClient::to_bin()
{
    alloc_data(CLIENT_MESSAGE_SIZE);
    memset(_data, 0, CLIENT_MESSAGE_SIZE);

    char *tmp = _data;

    memcpy(tmp, &type, sizeof(ClientMessageType));
    tmp += sizeof(ClientMessageType);

    memcpy(tmp, &input, sizeof(InputType));
    tmp += sizeof(InputType);

    memcpy(tmp, &win_width, sizeof(int));
    tmp += sizeof(int);

    memcpy(tmp, &win_height, sizeof(int));
    tmp += sizeof(int);

    memcpy(tmp, &pos, sizeof(Vector2D));
    tmp += sizeof(Vector2D);

    memcpy(tmp, &dim, sizeof(Vector2D));
    tmp += sizeof(Vector2D);

    memcpy(tmp, &rot, sizeof(float));
}

int TankMessageClient::from_bin(char *bobj)
{
    alloc_data(CLIENT_MESSAGE_SIZE);
    memcpy(static_cast<void *>(_data), bobj, CLIENT_MESSAGE_SIZE);

    char *tmp = _data;

    memcpy(&type, tmp, sizeof(ClientMessageType));
    tmp += sizeof(ClientMessageType);

    memcpy(&input, tmp, sizeof(InputType));
    tmp += sizeof(InputType);

    memcpy(&win_width, tmp, sizeof(int));
    tmp += sizeof(int);

    memcpy(&win_height, tmp, sizeof(int));
    tmp += sizeof(int);

    memcpy(&pos, tmp, sizeof(Vector2D));
    tmp += sizeof(Vector2D);

    memcpy(&dim, tmp, sizeof(Vector2D));
    tmp += sizeof(Vector2D);

    memcpy(&rot, tmp, sizeof(float));

    return 0;
}
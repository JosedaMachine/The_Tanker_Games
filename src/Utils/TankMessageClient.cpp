#include "TankMessageClient.h"
#include <iostream>

void TankMessageClient::setDefaultValues(const int &w_wL, const int &w_w, const int &w_hT, const int &w_h, const Vector2D &d, const float &r)
{
    std::cout << w_wL << "\n";
    std::cout << w_w << "\n";
    std::cout << w_hT << "\n";
    std::cout << w_h << "\n";

    win_widthL = w_wL; win_heightT = w_hT;
    win_width = w_w; win_height = w_h;
    dim = d; rot = r;
};

void TankMessageClient::setDefaultValues(const int &w_w, const int &w_h, const Vector2D &d, const float &r)
{
    win_width = w_w; win_height = w_h;
    dim = d; rot = r;
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

    memcpy(tmp, &win_widthL, sizeof(int));
    tmp += sizeof(int);

    memcpy(tmp, &win_width, sizeof(int));
    tmp += sizeof(int);

    memcpy(tmp, &win_heightT, sizeof(int));
    tmp += sizeof(int);

    memcpy(tmp, &win_height, sizeof(int));
    tmp += sizeof(int);

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

    memcpy(&win_widthL, tmp, sizeof(int));
    tmp += sizeof(int);

    memcpy(&win_width, tmp, sizeof(int));
    tmp += sizeof(int);

    memcpy(&win_heightT, tmp, sizeof(int));
    tmp += sizeof(int);

    memcpy(&win_height, tmp, sizeof(int));
    tmp += sizeof(int);

    memcpy(&dim, tmp, sizeof(Vector2D));
    tmp += sizeof(Vector2D);

    memcpy(&rot, tmp, sizeof(float));

    return 0;
}
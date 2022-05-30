#include "TankMessageServer.h"

void TankMessageServer::to_bin() {
    alloc_data(SERVER_MESSAGE_SIZE);
    memset(_data, 0, SERVER_MESSAGE_SIZE);

    char *tmp = _data;

    memcpy(tmp, &pos_t1, sizeof(Vector2D));
    tmp += sizeof(Vector2D);

    memcpy(tmp, &pos_t2, sizeof(Vector2D));
    tmp += sizeof(Vector2D);

    memcpy(tmp, &rot_t1, sizeof(float));
    tmp += sizeof(float);

    memcpy(tmp, &rot_t2, sizeof(float));
}

int TankMessageServer::from_bin(char * bobj)
{
    alloc_data(SERVER_MESSAGE_SIZE);
    memcpy(static_cast<void*>(_data), bobj, SERVER_MESSAGE_SIZE);

    char *tmp = _data;

    memcpy(&pos_t1, tmp, sizeof(Vector2D));
    tmp += sizeof(Vector2D);

    memcpy(&pos_t2, tmp, sizeof(Vector2D));
    tmp += sizeof(Vector2D);

    memcpy(&rot_t1, tmp, sizeof(float));
    tmp += sizeof(float);

    memcpy(&rot_t2, tmp, sizeof(float));

    return 0;
}
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
    tmp += sizeof(float);

    memcpy(tmp, &shoot, sizeof(bool));
    tmp += sizeof(bool);

    memcpy(tmp, &pos_bullet_1, sizeof(Vector2D));
    tmp += sizeof(Vector2D);

    memcpy(tmp, &pos_bullet_2, sizeof(Vector2D));
    tmp += sizeof(Vector2D);

    memcpy(tmp, &dim_bullet, sizeof(Vector2D));
    tmp += sizeof(Vector2D);

    memcpy(tmp, &type, sizeof(ServerMessageType));
    tmp += sizeof(ServerMessageType);

    memcpy(tmp, &action_, sizeof(ActionType));
    tmp += sizeof(ActionType);

    memcpy(tmp, &state, sizeof(ServerState));
    tmp += sizeof(ServerState);

    memcpy(tmp, &life, sizeof(int));
    tmp += sizeof(int);

    memcpy(tmp, &playerOneHasWon, sizeof(bool));
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
    tmp += sizeof(float);

    memcpy(&shoot, tmp, sizeof(bool));
    tmp += sizeof(bool);

    memcpy(&pos_bullet_1, tmp, sizeof(Vector2D));
    tmp += sizeof(Vector2D);

    memcpy(&pos_bullet_2, tmp, sizeof(Vector2D));
    tmp += sizeof(Vector2D);

    memcpy(&dim_bullet, tmp, sizeof(Vector2D));
    tmp += sizeof(Vector2D);

    memcpy(&type,tmp, sizeof(ServerMessageType));
    tmp += sizeof(ServerMessageType);

    memcpy(&action_, tmp, sizeof(ActionType));
    tmp += sizeof(ActionType);

    memcpy(&state, tmp, sizeof(ServerState));
    tmp += sizeof(ServerState);

    memcpy(&life, tmp, sizeof(int));
    tmp += sizeof(int);

    memcpy(&playerOneHasWon,tmp, sizeof(bool));

    return 0;
}
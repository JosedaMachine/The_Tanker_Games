#include "TankMessageClient.h"

void TankMessageClient::to_bin() {
    alloc_data(MESSAGE_SIZE);
    memset(_data, 0, MESSAGE_SIZE);

    char *tmp = _data;

    memcpy(tmp, &type, sizeof(ClientMessageType));
    tmp += sizeof(ClientMessageType);

    memcpy(tmp, &input, sizeof(InputType));
    tmp += sizeof(InputType);
}

int TankMessageClient::from_bin(char * bobj)
{
    alloc_data(MESSAGE_SIZE);
    memcpy(static_cast<void*>(_data), bobj, MESSAGE_SIZE);

    char *tmp = _data;

    memcpy(&type, tmp, sizeof(ClientMessageType));
    tmp += sizeof(ClientMessageType);

    memcpy(&input, tmp, sizeof(InputType));
    tmp += sizeof(InputType);

    return 0;
}
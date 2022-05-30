#include "TankMessageServer.h"
//REGISTRAR TECLAS Y MANDARLAS PARA QUE EL OTRO CLIENTE LAS PROCESE
void TankMessageServer::to_bin() {
    // alloc_data(MESSAGE_SIZE);
    // memset(_data, 0, MESSAGE_SIZE);

    // //Serializar los campos type, nick y message en el buffer _data
    // char *tmp = _data;

    // memcpy(tmp, &type, sizeof(uint8_t));
    // tmp += sizeof(uint8_t);

    // memcpy(tmp, nick.c_str(), NICK_SIZE);
    // tmp += NICK_SIZE;

    // memcpy(tmp, message.c_str(), MESSAGE_DATA_SIZE);
}

int TankMessageServer::from_bin(char * bobj)
{
    // alloc_data(MESSAGE_SIZE);
    // memcpy(static_cast<void*>(_data), bobj, MESSAGE_SIZE);

    // //Reconstruir la clase usando el buffer _data
    // char *tmp = _data;

    // memcpy(&type, tmp, sizeof(uint8_t));
    // tmp += sizeof(uint8_t);

    // nick = tmp;
    // tmp += NICK_SIZE;

    // message = tmp;

    return 0;
}
#include "TankServer.h"

#include <iostream>

#include "../Utils/TankMessageClient.h"

TankServer::TankServer(const char *s, const char *p) : server_socket(s, p)
{
    server_socket.bind();

    tank_1 = tank_2 = nullptr;
};

void TankServer::game_thread()
{
    while (true)
    {
        TankMessageClient client_recv_msg;
        Socket *client_player_sock = new Socket(server_socket);
        server_socket.recv(client_recv_msg, client_player_sock);

        switch (client_recv_msg.type)
        {
        case TankMessageClient::ClientMessageType::REGISTER:
        { // - REGISTER: register player on server data base
            printf("REGISTER\n");
            if(client_player_sock == nullptr)
                std::cout << "Is NULL\n";
            addPlayer(client_player_sock);

            break;
        }
        case TankMessageClient::ClientMessageType::QUIT:
        { // - QUIT: remove player from server data base
            printf("QUIT\n");

            removePlayer(client_player_sock);

            break;
        }
        case TankMessageClient::ClientMessageType::HANDLE_INPUT:
        { // - HANDLE_INPUT: handles input sent by client for next simulation step
            printf("HANDLE_INPUT\n");

            // TO DO: handle the input like actually fr fr
            break;
        }
        }
    }
}

void TankServer::addPlayer(Socket *player_sock)
{
    if ((tank_1 && player_sock == tank_1) || (tank_2 && player_sock == tank_2))
    {
        printf("Player already registered.\n");
        return;
    }

    if (tank_1 != nullptr && tank_2 != nullptr)
    {
        printf("Unable to register player, match already full.\n");
        return;
    }

    if (tank_1 == nullptr){
        tank_1 = player_sock;
        printf("Player One Ready.\n");
    }
    else{
        tank_2 = player_sock;
        printf("Player Two Ready.\n");
    }
}

void TankServer::removePlayer(Socket *player_sock)
{
    // I dont know if i should remove too, for now we just nullptr the reference
    if (*player_sock == *tank_1){
        printf("Player One Quit\n");
        tank_1 = nullptr;
    }
    else if (*player_sock == *tank_2){
        printf("Player Two Quit\n");
        tank_2 = nullptr;
    }
    else
        printf("Player was not registered previously.\n");
}



void TankServer::run()
{
    while(true){

    };
}
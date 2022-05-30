#include "TankServer.h"

#include <iostream>

TankServer::TankServer(const char *s, const char *p) : server_socket(s, p)
{
    server_socket.bind();

    tank_1 = tank_2 = nullptr;

    setup();
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

            if (client_player_sock == nullptr)
                std::cout << "Is NULL\n";

            addPlayer(client_player_sock);

            break;
        }
        case TankMessageClient::ClientMessageType::QUIT:
        { // - QUIT: remove player from server data base
            printf("QUIT\n");

            if (client_player_sock == nullptr)
                std::cout << "Is NULL\n";

            removePlayer(client_player_sock);

            break;
        }
        case TankMessageClient::ClientMessageType::HANDLE_INPUT:
        { // - HANDLE_INPUT: handles input sent by client for next simulation step
            printf("HANDLE_INPUT\n");

            input_mutex.lock(); // mutex lock so we don't modify values during run loop (handleInput())
            saveInput(client_player_sock, client_recv_msg.input);
            input_mutex.unlock();

            break;
        }
        }
    }
}

void TankServer::run()
{
    while (true)
    {
        input_mutex.lock(); // mutex lock so we are save from alterations
        handleInput();
        input_mutex.unlock();

        if (tank_1 != nullptr && tank_2 != nullptr){
            stepSimulation();
            usleep(TICK_RATE);
        }
    };
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

    if (tank_1 == nullptr)
    {
        tank_1 = player_sock;
        printf("Player One Ready.\n");
    }
    else
    {
        tank_2 = player_sock;
        printf("Player Two Ready.\n");
    }
}

void TankServer::removePlayer(Socket *player_sock)
{
    // I dont know if i should remove too, for now we just nullptr the reference
    if (tank_1 != nullptr && *player_sock == *tank_1)
    {
        printf("Player One Quit\n");
        tank_1 = nullptr;
    }
    else if (tank_2 != nullptr && *player_sock == *tank_2)
    {
        printf("Player Two Quit\n");
        tank_2 = nullptr;
    }
    else
        printf("Player was not registered previously.\n");
}

void TankServer::saveInput(Socket *player_sock, TankMessageClient::InputType input)
{
    if (*player_sock == *tank_1)
    {
        printf("Input T1.\n");
        input_t1 = input;
    }
    else if (*player_sock == *tank_2)
    {
        printf("Input T2.\n");
        input_t2 = input;
    }
    else
        printf("Trying to handle input from a non registered client.\n");
}

void TankServer::handleInput()
{
    // handle input player 1
    switch (input_t1)
    {
    case TankMessageClient::InputType::LEFT:
    {
        rot_t1 -= 5.0f;
    }
    break;
    case TankMessageClient::InputType::RIGHT:
    {
        rot_t1 += 5.0f;
    }
    break;
    case TankMessageClient::InputType::FRONT:
    {
        vel_t1 = vel_t1 + (Vector2D(0, -1).rotate(rot_t1) * 3.0);
    }
    break;
    case TankMessageClient::InputType::BACK:
    {
        vel_t1 = vel_t1 + (Vector2D(0, 1).rotate(rot_t1) * 2.0);
    }
    break;
    case TankMessageClient::InputType::SHOOT:
        break;
    case TankMessageClient::InputType::PLAY:
        break;
    case TankMessageClient::InputType::ESCAPE:
        break;
    case TankMessageClient::InputType::NONE:
    default:
    {
        vel_t1 = Vector2D(0, 0);
    }
    break;
    }

    // handle input player 2
    switch (input_t2)
    {
    case TankMessageClient::InputType::LEFT:
    {
        rot_t2 -= 5.0f;
    }
    break;
    case TankMessageClient::InputType::RIGHT:
    {
        rot_t2 += 5.0f;
    }
    break;
    case TankMessageClient::InputType::FRONT:
    {
        vel_t2 = vel_t2 + (Vector2D(0, -1).rotate(rot_t2) * 3.0);
    }
    break;
    case TankMessageClient::InputType::BACK:
    {
        vel_t2 = vel_t2 + (Vector2D(0, 1).rotate(rot_t2) * 2.0);
    }
    case TankMessageClient::InputType::SHOOT:
        break;
    case TankMessageClient::InputType::PLAY:
        break;
    case TankMessageClient::InputType::ESCAPE:
        break;
    case TankMessageClient::InputType::NONE:
    default:
    {
        vel_t2 = Vector2D(0, 0);
    }
    break;
    }

    // reset input
    input_t1 = input_t2 = TankMessageClient::InputType::NONE;
};

void TankServer::setup()
{
    input_t1 = input_t2 = TankMessageClient::InputType::NONE;
    pos_t1 = Vector2D(200, 360);
    pos_t2 = Vector2D(800, 360);
    vel_t1 = vel_t2 = Vector2D(0, 0);
    rot_t1 = rot_t2 = 0;
}

void TankServer::stepSimulation()
{
    pos_t1 = pos_t1 + vel_t1;
    pos_t2 = pos_t2 + vel_t2;

    std::cout << pos_t1 << " " << pos_t2 << "\n";

    TankMessageServer msg(pos_t1, pos_t2, rot_t1, rot_t2);
    server_socket.send(msg, *tank_1);
    server_socket.send(msg, *tank_2);
}
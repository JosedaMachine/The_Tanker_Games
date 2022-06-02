#include "TankServer.h"
#include <time.h>
#include <iostream>

#include <SDL2/SDL.h>

#include "../../Utils/Collisions.h"

TankServer::TankServer(const char *s, const char *p) : server_socket(s, p), dim_b(15, 15)
{
    srand((unsigned)time(NULL));

    server_socket.bind();

    tank_1 = tank_2 = nullptr;
    dim_t1 = dim_t2 = Vector2D(0, 0);

    state = TankMessageServer::ServerState::WAITING;

    reset();
};

void TankServer::reset()
{
    input_t1 = input_t2 = TankMessageClient::InputType::NONE;
    pos_t1 = Vector2D(200, 360);
    pos_t2 = Vector2D(800, 360);
    vel_t1 = vel_t2 = Vector2D(0, 0);
    rot_t1 = rot_t2 = 0;

    shoot_t1 = false;
    pos_b1 = vel_b1 = Vector2D(0, 0);
    pos_b2 = vel_b2 = Vector2D(0, 0);

    t1_ready = false;
    t2_ready = false;
    lifeT1 = lifeT2 = 3;

    obstacles_.clear();
}

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
            int pl;
            if (addPlayer(client_player_sock, pl))
                initPlayer(pl, &client_recv_msg);

            if (tank_1 != nullptr && tank_2 != nullptr)
                state = TankMessageServer::ServerState::READY;
            else
                state = TankMessageServer::ServerState::WAITING;

            sendStateMessage();
        }
        break;
        case TankMessageClient::ClientMessageType::QUIT:
        { // - QUIT: remove player from server data base
            removePlayer(client_player_sock);

            if (tank_1 == nullptr || tank_2 == nullptr)
            {
                state = TankMessageServer::ServerState::WAITING;
                sendStateMessage();
            }
        }
        break;
        case TankMessageClient::ClientMessageType::HANDLE_INPUT:
        { // - HANDLE_INPUT: handles input sent by client for next simulation step

            input_mutex.lock(); // mutex lock so we don't modify values during run loop (handleInput())
            saveInput(client_player_sock, client_recv_msg.input);
            input_mutex.unlock();
        }
        break;
        }
    }
}

void TankServer::createObstacles()
{
    int numberObstacles = 6;

    int minX = 0;
    int maxX = win_width - 200;

    int minY = 0;
    int maxY = win_height - 200;

    int minDim = 40;
    int maxDim = 100;
    const int threshold_dim = 10;
    for (size_t i = 0; i < numberObstacles; i++)
    {
        int auxDim = (maxDim - minDim) * ((float)rand() / RAND_MAX) + minDim;

        Vector2D dim(auxDim, auxDim);

        Vector2D pos((maxX - minX) * ((float)rand() / RAND_MAX) + minX, (maxY - minY) * ((float)rand() / RAND_MAX) + minY);
        while (Collisions::collidesWithRotation(pos_t1, dim_t1.getX(), dim_t1.getY(), rot_t1,
                                                pos, dim.getX() + threshold_dim, dim.getY() + threshold_dim, 0) || // Mientras se solape con el tanque 1
               Collisions::collidesWithRotation(pos_t2, dim_t2.getX(), dim_t2.getY(), rot_t2,
                                                pos, dim.getX() + threshold_dim, dim.getY() + threshold_dim, 0) || // O con el tanque 2
               outOfBounds(pos, dim, Vector2D(maxX, maxY)))                                                        // O se salga de la pantalla
            // Buscamos nuevas posiciones
            pos = Vector2D((maxX - minX) * ((float)rand() / RAND_MAX) + minX, (maxY - minY) * ((float)rand() / RAND_MAX) + minY);

        Obstacle obs;
        obs.dim = dim;
        obs.pos = pos;
        obstacles_.push_back(obs);

        TankMessageServer msg(pos, dim);
        msg.type = TankMessageServer::TankMessageServer::ACTION;
        msg.action_ = TankMessageServer::ActionType::CREATE_OBSTACLE;
        server_socket.send(msg, *tank_1);
        server_socket.send(msg, *tank_2);
    }
}

void TankServer::run()
{
    while (true)
    {
        input_mutex.lock(); // mutex lock so we are save from alterations
        handleInput();
        input_mutex.unlock();

        if (state == TankMessageServer::ServerState::READY && t1_ready && t2_ready)
        {
            state = TankMessageServer::ServerState::PLAYING;
            t1_ready = t2_ready = false;
            timer = 0;
            createObstacles();
            sendStateMessage();
        }

        if (state == TankMessageServer::ServerState::PLAYING)
        {
            stepSimulation();
            updateInfoClients();
            usleep(TICK_RATE);
        }

        Uint32 startTime = SDL_GetTicks();
        if (state == TankMessageServer::ServerState::GAME_OVER)
        {
            Uint32 frameTime = SDL_GetTicks() - startTime;
            if(timer <= 3500)
                timer += frameTime;
            else 
            {
                state = TankMessageServer::ServerState::READY;
                sendStateMessage();
            }
        }
    };
}

bool TankServer::addPlayer(Socket *player_sock, int &pl)
{
    if ((tank_1 && *player_sock == *tank_1) || (tank_2 && *player_sock == *tank_2))
    {
        printf("Player already registered.\n");
        return false;
    }

    if (tank_1 != nullptr && tank_2 != nullptr)
    {
        printf("Unable to register player, match already full.\n");
        return false;
    }

    if (tank_1 == nullptr)
    {
        tank_1 = player_sock;
        pl = 0;
        printf("Registered. Player One Ready.\n");
    }
    else
    {
        tank_2 = player_sock;
        pl = 1;
        printf("Registered. Player Two Ready.\n");
    }
    return true;
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

void TankServer::initPlayer(const int &pl, const TankMessageClient *msg)
{
    win_width = msg->win_width;
    win_height = msg->win_height;

    if (!pl)
    {
        dim_t1 = msg->dim;
        rot_t1 = msg->rot;
    }
    else
    {
        dim_t2 = msg->dim;
        rot_t2 = msg->rot;
    }
}

void TankServer::saveInput(Socket *player_sock, TankMessageClient::InputType input)
{
    if (*player_sock == *tank_1)
        input_t1 = input;
    else if (*player_sock == *tank_2)
        input_t2 = input;
    else
        printf("Trying to handle input from a non registered client.\n");
}

void TankServer::handleInput()
{
    // handle input player 1
    switch (input_t1)
    {
    case TankMessageClient::InputType::LEFT:
        rot_t1 -= 5.0f;
    break;
    case TankMessageClient::InputType::RIGHT:
        rot_t1 += 5.0f;
    break;
    case TankMessageClient::InputType::FRONT:
        vel_t1 = vel_t1 + (Vector2D(0, -1).rotate(rot_t1) * 3.0);
    break;
    case TankMessageClient::InputType::BACK:
        vel_t1 = vel_t1 + (Vector2D(0, 1).rotate(rot_t1) * 2.0);
    break;
    case TankMessageClient::InputType::SHOOT:
    {
        if (!shoot_t1)
        {
            shoot_t1 = true;
            printf("Shoot 1.\n");
            pos_b1 = pos_t1 + Vector2D(dim_t1.getX() / 2.0f, dim_t1.getY() / 2.0f) - Vector2D(0.0f, dim_t1.getY() / 2.0f + 12.0f).rotate(rot_t1) - Vector2D(0, 10.0f);

            vel_b1 = Vector2D(0, -1).rotate(rot_t1) * 5.0f;

            TankMessageServer msg(pos_b1, dim_b);
            msg.type = TankMessageServer::TankMessageServer::ACTION;
            msg.action_ = TankMessageServer::ActionType::CREATE_BULLET_1;
            server_socket.send(msg, *tank_1);
            server_socket.send(msg, *tank_2);
        }
    }
    break;
    case TankMessageClient::InputType::PLAY:
        t1_ready = true;
    break;
    case TankMessageClient::InputType::NONE:
    default:
        vel_t1 = Vector2D(0, 0);
    break;
    }

    // handle input player 2
    switch (input_t2)
    {
    case TankMessageClient::InputType::LEFT:
        rot_t2 -= 5.0f;
    break;
    case TankMessageClient::InputType::RIGHT:
        rot_t2 += 5.0f;
    break;
    case TankMessageClient::InputType::BACK:
        vel_t2 = vel_t2 + (Vector2D(0, 1).rotate(rot_t2) * 2.0);
    break;
    case TankMessageClient::InputType::SHOOT:
    {
        if (!shoot_t2)
        {
            shoot_t2 = true;
            printf("Shoot 2.\n");
            pos_b2 = pos_t2 + Vector2D(dim_t2.getX() / 2.0f, dim_t2.getY() / 2.0f) - Vector2D(0.0f, dim_t2.getY() / 2.0f + 12.0f).rotate(rot_t2) - Vector2D(0, 10.0f);

            vel_b2 = Vector2D(0, -1).rotate(rot_t2) * 5.0f;

            TankMessageServer msg(pos_b2, dim_b);
            msg.type = TankMessageServer::TankMessageServer::ACTION;
            msg.action_ = TankMessageServer::ActionType::CREATE_BULLET_2;
            server_socket.send(msg, *tank_1);
            server_socket.send(msg, *tank_2);
        }
    }
    break;
    case TankMessageClient::InputType::PLAY:
        t2_ready = true;
    break;
    case TankMessageClient::InputType::NONE:
    default:
        vel_t2 = Vector2D(0, 0);
    break;
    }

    // reset input
    input_t1 = input_t2 = TankMessageClient::InputType::NONE;
};

void TankServer::stepSimulation()
{
    if (!outOfBounds(pos_t1 + vel_t1, dim_t1))
        pos_t1 = pos_t1 + vel_t1;
    if (!outOfBounds(pos_t2 + vel_t2, dim_t2))
        pos_t2 = pos_t2 + vel_t2;

    if (shoot_t1)
    {
        if (!outOfBounds(pos_b1 + vel_b1, dim_b))
            pos_b1 = pos_b1 + vel_b1;
        else
        {
            shoot_t1 = false;

            TankMessageServer msg;
            msg.type = TankMessageServer::TankMessageServer::ACTION;
            msg.action_ = TankMessageServer::ActionType::DESTROY_BULLET_1;
            server_socket.send(msg, *tank_1);
            server_socket.send(msg, *tank_2);
        }
    }

    if (shoot_t2)
    {
        if (!outOfBounds(pos_b2 + vel_b2, dim_b))
            pos_b2 = pos_b2 + vel_b2;
        else
        {
            shoot_t2 = false;

            TankMessageServer msg;
            msg.type = TankMessageServer::TankMessageServer::ACTION;
            msg.action_ = TankMessageServer::ActionType::DESTROY_BULLET_2;
            server_socket.send(msg, *tank_1);
            server_socket.send(msg, *tank_2);
        }
    }

    checkCollisions();
}

void TankServer::updateInfoClients()
{
    TankMessageServer msg(pos_t1, pos_t2, rot_t1, rot_t2, shoot_t1, pos_b1, pos_b2);
    msg.type = TankMessageServer::ServerMessageType::UPDATE_INFO;
    server_socket.send(msg, *tank_1);
    server_socket.send(msg, *tank_2);
}

bool TankServer::outOfBounds(const Vector2D pos, Vector2D &dim)
{
    return pos.getX() < 0 || pos.getY() < 0 ||
           pos.getX() + dim.getX() > win_width ||
           pos.getY() + dim.getY() > win_height;
}

bool TankServer::outOfBounds(const Vector2D pos, Vector2D &dim, const Vector2D &limit)
{
    return pos.getX() < 0 || pos.getY() < 0 ||
           pos.getX() + dim.getX() > limit.getX() ||
           pos.getY() + dim.getY() > limit.getY();
}

void TankServer::checkCollisions()
{
    if (Collisions::collidesWithRotation(pos_t1, dim_t1.getX(), dim_t1.getY(), rot_t1,
                                         pos_t2, dim_t2.getX(), dim_t2.getY(), rot_t2))
    {
        pos_t1 = pos_t1 - vel_t1;
        pos_t2 = pos_t2 - vel_t2;
        printf("Tanques Colisionan\n");
    }

    // Obstacles collision
    for (size_t i = 0; i < obstacles_.size(); i++)
    {
        // Tank1 collides with obstacle
        if (Collisions::collidesWithRotation(pos_t1, dim_t1.getX(), dim_t1.getY(), rot_t1,
                                             obstacles_[i].pos, obstacles_[i].dim.getX(), obstacles_[i].dim.getY(), 0))
            pos_t1 = pos_t1 - vel_t1;

        // Tank2 collides with obstacle
        if (Collisions::collidesWithRotation(pos_t2, dim_t2.getX(), dim_t2.getY(), rot_t2,
                                             obstacles_[i].pos, obstacles_[i].dim.getX(), obstacles_[i].dim.getY(), 0))
            pos_t2 = pos_t2 - vel_t2;

        // Bullet 2 collides with obstacle
        if (shoot_t1 && Collisions::collidesWithRotation(pos_b1, dim_b.getX(), dim_b.getY(), 0,
                                                         obstacles_[i].pos, obstacles_[i].dim.getX(), obstacles_[i].dim.getY(), 0))
        {
            shoot_t1 = false;
            TankMessageServer msg;
            msg.type = TankMessageServer::TankMessageServer::ACTION;
            msg.action_ = TankMessageServer::ActionType::DESTROY_BULLET_1;
            server_socket.send(msg, *tank_1);
            server_socket.send(msg, *tank_2);
        }

        // Bullet 2 collides with obstacle
        if (shoot_t2 && Collisions::collidesWithRotation(pos_b2, dim_b.getX(), dim_b.getY(), 0,
                                                         obstacles_[i].pos, obstacles_[i].dim.getX(), obstacles_[i].dim.getY(), 0))
        {
            shoot_t2 = false;
            TankMessageServer msg;
            msg.type = TankMessageServer::TankMessageServer::ACTION;
            msg.action_ = TankMessageServer::ActionType::DESTROY_BULLET_2;
            server_socket.send(msg, *tank_1);
            server_socket.send(msg, *tank_2);
        }
    }

    // Tank 1 With Bullet 2
    if (shoot_t2 && Collisions::collidesWithRotation(pos_t1, dim_t1.getX(), dim_t1.getY(), rot_t1,
                                                     pos_b2, dim_b.getX(), dim_b.getY(), 0))
    {
        printf("Tank1: Ouch\n");

        shoot_t2 = false;
        if (lifeT1 > 0)
            lifeT1--;

        if (lifeT1 <= 0)
        {
            state = TankMessageServer::ServerState::GAME_OVER;
            sendStateMessage();
        }
        else
        {
            TankMessageServer msg(lifeT1);
            msg.type = TankMessageServer::TankMessageServer::ACTION;
            msg.action_ = TankMessageServer::ActionType::DAMAGE_1;
            server_socket.send(msg, *tank_1);
            server_socket.send(msg, *tank_2);
        }
    }

    // Tank 2 With Bullet 1
    if (shoot_t1 && Collisions::collidesWithRotation(pos_t2, dim_t2.getX(), dim_t2.getY(), rot_t2,
                                                     pos_b1, dim_b.getX(), dim_b.getY(), 0))
    {
        printf("Tank2: Ouch\n");

        shoot_t1 = false;
        if (lifeT2 > 0)
            lifeT2--;

        if (lifeT2 <= 0)
        {
            state = TankMessageServer::ServerState::GAME_OVER;
            sendStateMessage();
        }
        else
        {
            TankMessageServer msg(lifeT2);
            msg.type = TankMessageServer::TankMessageServer::ACTION;
            msg.action_ = TankMessageServer::ActionType::DAMAGE_2;
            server_socket.send(msg, *tank_1);
            server_socket.send(msg, *tank_2);
        }
    }
}

void TankServer::sendStateMessage()
{
    TankMessageServer msg(state);
    msg.type = TankMessageServer::TankMessageServer::UPDATE_STATE;

    if (tank_1 != nullptr)
        server_socket.send(msg, *tank_1);
    if (tank_2 != nullptr)
        server_socket.send(msg, *tank_2);

    if (state != TankMessageServer::ServerState::PLAYING)
        reset();
}
#include "TankServer.h"
#include "TankMessage.h"

TankServer::TankServer(const char * s, const char * p): server_socket(s, p) {
    server_socket.bind();

    tank_1 = tank_2 = nullptr;
};

void TankServer::searchingPlayers(){
    waitForPlayer(tank_1);
    waitForPlayer(tank_2);
}

void TankServer::waitForPlayer(Socket* tank){
    while(tank == nullptr){
        TankMessage receptor;
        Socket* player;   
        server_socket.recv(receptor, player);
        if(receptor.type == TankMessage::MessageType::REGISTER){
            tank = player;
        }
    }
}

void TankServer::start() {
    // while (true) {
    //     /*
    //      * NOTA: los clientes están definidos con "smart pointers", es necesario
    //      * crear un unique_ptr con el objeto socket recibido y usar std::move
    //      * para añadirlo al vector
    //      */
    //     ChatMessage client_message;
    //     Socket* client_socket = new Socket(socket);
    //     socket.recv(client_message, client_socket);

    //     switch (client_message.type) {
    //     case ChatMessage::LOGIN: { // - LOGIN: Añadir al vector clients
    //         printf("LOG IN: ");
    //         std::cout << client_message.nick << "\n";
            
    //         auto message_ptr = std::make_unique<Socket>(*client_socket); client_socket = nullptr;
    //         clients.push_back(std::move(message_ptr));

    //         break;
    //     }
    //     case ChatMessage::LOGOUT: { // - LOGOUT: Eliminar del vector clients
    //         printf("LOG OUT: ");
    //         std::cout << client_message.nick << "\n";

    //         auto clients_it = clients.begin();
    //         while(clients_it != clients.end() && *(*clients_it) != *client_socket) clients_it++;

    //         if(clients_it != clients.end()) clients.erase(clients_it);
    //         else std::cout << "Invalid socket: " << client_socket << "\n";
            
    //         break;
    //     }
    //     case ChatMessage::MESSAGE: { // - MESSAGE: Reenviar el mensaje a todos los clientes (menos el emisor)
    //         printf("MESSAGE: ");
    //         std::cout << client_message.nick << " -> " << client_message.message << "\n";

    //         for(auto clients_it = clients.begin(); clients_it != clients.end(); clients_it++)
    //             if(*(*clients_it) != *client_socket)
    //                 socket.send(client_message, **clients_it);
    //         break;
    //     }
    //     }
    // }
}
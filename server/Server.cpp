#include "Server.h"
#include <stdio.h>
#include <stdlib.h>
#include <sstream>


Server::Server() {
#ifdef _WIN32
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif
    server_socket_ = socket(AF_INET, SOCK_STREAM, 0);

    int opt = 1;
    setsockopt(server_socket_, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));

    struct sockaddr_in socket_info;
    socket_info.sin_family = AF_INET;
    socket_info.sin_addr.s_addr = INADDR_ANY;
    socket_info.sin_port = htons(1337);

    bind(server_socket_, (struct sockaddr*)&socket_info, sizeof(socket_info));
    listen(server_socket_, 3);
}

void Server::interactWithClient(SOCKET sfd, std::shared_ptr<Player> player) {
    auto result = game_->getSerializedGameState(player);
    char *msg = result.data();
    send(sfd, msg, 10000, 0);

    char reply_from_client[100];
    recv(sfd, reply_from_client, 100, 0);

    std::string type;
    Point where;
    std::stringstream(reply_from_client) >> type >> where;
    player->catchClick(type, where);
}


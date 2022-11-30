#include "Server.h"
#include <stdio.h>
#include <stdlib.h>
#include <sstream>


Server::Server() {
#ifdef _WIN32
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif
}

Server::~Server() {
#ifdef _WIN32
    shutdown(server_socket_, SD_BOTH);
    closesocket(server_socket_);
    WSACleanup();
#else
    close(server_socket_);
#endif
}

Server& Server::startListeningOnPort(unsigned short port) {
    server_socket_ = socket(AF_INET, SOCK_STREAM, 0);

    int opt = 1;
    setsockopt(server_socket_, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));

    struct sockaddr_in socket_info;
    socket_info.sin_family = AF_INET;
    socket_info.sin_addr.s_addr = INADDR_ANY;
    socket_info.sin_port = htons(port);

    bind(server_socket_, (struct sockaddr*)&socket_info, sizeof(socket_info));
    listen(server_socket_, 3);

    return *this;
}

Server& Server::waitForPlayers() {
    fd_set readfds;
    int max_sd;
    struct timeval zero_tv = { 0 };
    struct sockaddr_in socket_info;
    socklen_t socket_info_len = sizeof(socket_info);
    std::size_t connected = 0;
    while (connected != 2) {
        FD_ZERO(&readfds);
        FD_SET(server_socket_, &readfds);
        max_sd = server_socket_;

        select((int)max_sd + 1, &readfds, NULL, NULL, &zero_tv);

        if (FD_ISSET(server_socket_, &readfds)) {
            client_socket_[connected] = accept(server_socket_, (struct sockaddr*)&socket_info, &socket_info_len);
            printf("New connection , socket fd is %d , ip is : %s , port : %d\n", client_socket_[connected], inet_ntoa(socket_info.sin_addr), ntohs(socket_info.sin_port));

            connected++;
        }
    }

    return *this;
}

void Server::interactWithClient(SOCKET sfd, std::shared_ptr<Player> player) {
    char reply_from_client[100];
    int received_bytes = recv(sfd, reply_from_client, 100, 0);

    if (received_bytes != 100) {
        return;
    }

    std::string type;
    Point where;
    std::stringstream(reply_from_client) >> type >> where;
    player->catchClick(type, where);
}


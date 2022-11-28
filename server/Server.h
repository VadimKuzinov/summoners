#pragma once
#ifdef __linux__
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#define SOCKET int
#elif _WIN32
#ifndef UNICODE
#define UNICODE 1
#endif
#pragma comment(lib,"Ws2_32.lib")
#include <WinSock2.h>
#include <WS2tcpip.h>
#endif
#include "Game.h"
#include "FPSHandler.h"
#include <memory>


class Server {
private:
    std::unique_ptr<Game> game_;
    SOCKET server_socket_;

private:
    void interactWithClient(SOCKET sfd, std::shared_ptr<Player>);

public:
    Server& startListeningOnPort(unsigned short port);

    Server& createGame(const std::string& academy_cfg, const std::string& map_cfg) {
        game_ = std::make_unique<Game>(academy_cfg, map_cfg);
        return *this;
    }

    template <std::size_t fps_v>
    void runWithFps();
};

template <std::size_t fps_v>
void Server::runWithFps() {
    SOCKET new_socket, max_sd;
    std::pair<SOCKET, SOCKET> client_sfd_pair = { 0, 0 };

    struct timeval zero_tv = { 0 };
    struct sockaddr_in socket_info;
    socklen_t socket_info_len = sizeof(socket_info);

    fd_set readfds;

    bool players_are_ready = false;

    for (FPSHandler<fps_v> fps_handler; ; fps_handler.sleep()) {
        FD_ZERO(&readfds);
        FD_SET(server_socket_, &readfds);
        max_sd = server_socket_;

        if (client_sfd_pair.first > 0) {
            FD_SET(client_sfd_pair.first, &readfds);
        }
        if (client_sfd_pair.second > 0) {
            FD_SET(client_sfd_pair.second, &readfds);
        }

        if (client_sfd_pair.first && client_sfd_pair.second) {
            players_are_ready = true;
        }

        max_sd = std::max(max_sd, std::max(client_sfd_pair.first, client_sfd_pair.second));

        select((int)max_sd + 1, &readfds, NULL, NULL, &zero_tv);

        if (!players_are_ready && FD_ISSET(server_socket_, &readfds)) {
            new_socket = accept(server_socket_, (struct sockaddr*)&socket_info, &socket_info_len);
            printf("New connection , socket fd is %d , ip is : %s , port : %d\n", new_socket, inet_ntoa(socket_info.sin_addr), ntohs(socket_info.sin_port));

            (client_sfd_pair.first == 0 ? client_sfd_pair.first : client_sfd_pair.second) = new_socket;
        }

        if (FD_ISSET(client_sfd_pair.first, &readfds)) {
            interactWithClient(client_sfd_pair.first, game_->getFirstPlayer());
        }

        if (FD_ISSET(client_sfd_pair.second, &readfds)) {
            interactWithClient(client_sfd_pair.second, game_->getSecondPlayer());
        }

        game_->getTerrain()->goToTheNextIteration();
    }
}


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
#pragma comment(lib, "Ws2_32.lib")
#include <WinSock2.h>
#include <WS2tcpip.h>
#endif
#include "Game.h"
#include <memory>


class Server {
private:
    std::unique_ptr<Game> game_;
    SOCKET server_socket_;
    int client_socket_[2] = { 0, 0 };

private:
    void interactWithClient(SOCKET sfd, std::shared_ptr<Player>);

public:
    Server();
    ~Server();

    Server& startListeningOnPort(unsigned short port);

    Server& createGame(const std::string& academy_cfg, const std::string& map_cfg) {
        game_ = std::make_unique<Game>(academy_cfg, map_cfg);
        return *this;
    }

    Server& waitForPlayers();

    template <std::size_t fps_v>
    void runWithFps();
};

template <std::size_t fps_v>
void Server::runWithFps() {
    struct timeval zero_tv = { 0 };

    fd_set readfds;

    using frames = std::chrono::duration<int64_t, std::ratio<1, fps_v>>;
    auto next_frame = std::chrono::time_point_cast<frames>(std::chrono::system_clock::now()) + frames{ 1 };

    int max_sd = std::max(client_socket_[0], client_socket_[1]);
    std::vector<char> game_state;
    while (true) {
        FD_ZERO(&readfds);

        FD_SET(client_socket_[0], &readfds);
        FD_SET(client_socket_[1], &readfds);

        select((int)max_sd + 1, &readfds, NULL, NULL, &zero_tv);

        send(client_socket_[0], game_->getSerializedGameState(game_->getFirstPlayer()).data(), 10000, 0);
        send(client_socket_[1], game_->getSerializedGameState(game_->getSecondPlayer()).data(), 10000, 0);

        if (FD_ISSET(client_socket_[0], &readfds)) {
            interactWithClient(client_socket_[0], game_->getFirstPlayer());
        }

        if (FD_ISSET(client_socket_[1], &readfds)) {
            interactWithClient(client_socket_[1], game_->getSecondPlayer());
        }

        if (std::chrono::time_point_cast<frames>(std::chrono::system_clock::now()) >= next_frame) {
            game_->getTerrain()->goToTheNextIteration();
            next_frame += frames{ 1 };
        }
    }
}


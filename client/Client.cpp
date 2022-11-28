#ifdef __linux__
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#elif _WIN32
#ifndef UNICODE
#define UNICODE 1
#endif
#pragma comment(lib,"Ws2_32.lib")
#include <WinSock2.h>
#include <WS2tcpip.h>
#endif

#include "Client.h"
#include <sstream>
#include <stdlib.h>
#include <string>
#include <chrono>


Client& Client::connectToServerOnPort(unsigned short port) {
#ifdef _WIN32
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2,2), &wsaData);
#endif
    struct sockaddr_in client_info = {0};
    client_info.sin_family = AF_INET;
    client_info.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    client_info.sin_port = htons(port);
    socklen_t client_info_len = sizeof(client_info);
    sfd_ = socket(AF_INET, SOCK_STREAM, 0);
    connect(sfd_, (struct sockaddr*)&client_info, client_info_len);
    return *this;
}

void Client::act() {
    std::string default_msg = "none 0 0";
    char buf[10000];
    using frames = std::chrono::duration<int64_t, std::ratio<1, 64>>;
    auto next_frame = std::chrono::system_clock::now() + frames{1};
    std::string to_send;
    send(sfd_, default_msg.c_str(), 100, 0);
    int received_bytes = 0;
    while (true) {
        received_bytes = recv(sfd_, buf, 10000, 0);
            
        //std::cout << "Receieved:\n" << buf << std::endl;

        if (received_bytes == 10000) {
            handleData(buf);
        }

        if (std::chrono::system_clock::now() >= next_frame) {
            drawer_->draw();
            next_frame += frames{1};
        }

        to_send = getMessageFromEvent(default_msg);
        if (to_send == "") {
            break;
        }

        send(sfd_, to_send.c_str(), 100, 0);
    }
}

std::string Client::getMessageFromEvent(const std::string& default_msg) {
    std::string to_send = default_msg;
    //static std::string prev_to_send = default_msg;

    std::pair<std::string, Point> caught;
    SDL_Event event;
    int x, y;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            to_send = "";
            break;
        case SDL_MOUSEBUTTONDOWN:
            SDL_GetMouseState(&x, &y);
            caught = drawer_->catchClick(x, y);
            //prev_to_send = to_send;
            to_send = caught.first + " " + std::string(caught.second);
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_a) {
      //          to_send = prev_to_send;
            }
            break;
        default:
            break;
        }
    }

    return to_send;
}

void Client::handleData(char* data) {
    auto received = std::string(data);
    auto ss = std::stringstream(received);
    std::vector<std::vector<std::string>> widgets(3);
    std::size_t qty;
    std::string s;
    for (auto it = 0; it < 3; ++it) {
        ss >> qty;
        ss.ignore(1);
        while (qty--) {
            std::getline(ss, s);
            widgets[it].push_back(s);
        }
    }

    drawer_->receiveData(widgets[0], widgets[1], widgets[2]);
}

#pragma once
#include "Drawer.h"
#include <memory>


class Client {
private:
    std::unique_ptr<Drawer> drawer_;
    int sfd_ = -1;

public:
    Client& createDrawer(int width, int height, const std::string& cfg_filename) {
        drawer_ = std::make_unique<Drawer>(width, height, cfg_filename);
        return *this;
    }

    Client& connectToServerOnPort(unsigned short port);

    void act();
    void handleData(char* data);
    std::string getMessageFromEvent(const std::string&);
};


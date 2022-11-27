#pragma once
#include "Drawer.h"


class Client {
private:
    Drawer* drawer_;
    int sfd_ = -1;

public:
    explicit Client(Drawer* drawer) : drawer_(drawer) {
    }

    void connectToServer();
    void act();
    void handleData(char* data);
    std::string getMessageFromEvent(const std::string&);
};


#include "server/Server.h"
#include <iostream>


int main() {
    Server server;
    server.createGame("../../../cfg/academy", "../../../cfg/map3");
    server.run<64>();
    return 0;
}

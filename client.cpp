#include "client/Client.h"


int main(int argc, char* argv[]) {
    auto drawer = new Drawer(1746, 918, "../../../cfg/all");
    auto client = new Client(drawer);
    client->connectToServer();
    client->act();
    return 0;
}

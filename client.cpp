#include "client/Client.h"


int main(int argc, char* argv[]) {
    Client()
        .createDrawer(1746, 918, "../../../cfg/all")
        .connectToServerOnPort(1337)
        .act();
    return 0;
}

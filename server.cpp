#include "server/Server.h"


int main(int argc, char* argv[]) {
    Server()
        .startListeningOnPort(1337)
        .createGame("../../../cfg/academy", "../../../cfg/map3")
        .runWithFps<60>();
    return 0;
}

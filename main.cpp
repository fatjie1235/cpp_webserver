#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "TcpServer.h"

int main(int argc, char *argv[])
{
    unsigned short port = 10000;
    const char *path = "/data/Desktop/cpp_reactor/source/";

    if (argc >= 3)
    {
        port = atoi(argv[1]);
        path = argv[2];
    }
    else if (argc == 2)
    {
        port = atoi(argv[1]);
    }

    chdir(path);

    TcpServer server(port, 4);
    server.run();

    return 0;
}
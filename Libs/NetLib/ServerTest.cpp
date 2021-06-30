#include <Api/NetLib.h>
using namespace LunaLux::net;

int main()
{
    if(netInit() != NetResult::SUCSESS)
    {
        printf("SERVER: failed to load net lib\n");
        exit(-1);
    }

    if(connect("localhost:25565") != NetResult::SUCSESS)
    {
        printf("SERVER: failed to connect\n");
        exit(-1);
    }

    while (true)
    {
        if(waitForClientConnection() != NetResult::SUCSESS) exit(-1);

        auto data = receive(4);

        printf("SERVER: data got - %s\n",data);
        fflush(stdout);

        if(send(data, 4) != NetResult::SUCSESS)
        {
            printf("SERVER: failed to send message\n");
        }
        else break;
    }

    if(disconnect() != NetResult::SUCSESS)
    {
        printf("SERVER: failed to disconnect\n");
        exit(-1);
    }

    terminate();
    return 0;
}
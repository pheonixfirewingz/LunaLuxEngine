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
        WaitReturn waitReturn = waitForClientConnection();
        if(waitReturn.result != NetResult::SUCSESS) exit(-1);

        std::string data(receive(4),waitReturn.id);
        if(data == "ping")
        {
            char * ret = "pong";
            if (send(ret, 4,waitReturn.id) != NetResult::SUCSESS)
            {
                printf("SERVER: failed to send message\n");
            }
        }
    }

    if(disconnect() != NetResult::SUCSESS)
    {
        printf("SERVER: failed to disconnect\n");
        exit(-1);
    }

    terminate();
    return 0;
}
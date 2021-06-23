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

    while (waitForClientConnection() != NetResult::ERROR)
    {
        void* data;
        if(receive(&data,4) != NetResult::SUCSESS)
        {
            printf("SERVER: failed to receive message\n");
        }

        printf("SERVER: data got - %s",reinterpret_cast<char*>(data));

        if(send(data, 4) != NetResult::SUCSESS)
        {
            printf("SERVER: failed to send message\n");
            break;
        }
        free(data);
    }

    if(disconnect() != NetResult::SUCSESS)
    {
        printf("SERVER: failed to disconnect\n");
        exit(-1);
    }

    terminate();
    return 0;
}
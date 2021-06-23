#include <Api/NetLib.h>
using namespace LunaLux::net;

int main()
{
    if(netInit() != NetResult::SUCSESS)
    {
        printf("CLIENT: failed to load net lib\n");
        exit(-1);
    }

    setNetworkType(NetworkType::CLIENT);

    if(connect("localhost:25565") != NetResult::SUCSESS)
    {
        printf("CLIENT: failed to connect\n");
        exit(-1);
    }

    const char* msg = "ping";
    if(send(reinterpret_cast<const void*>(msg), sizeof(char) * 4) != NetResult::SUCSESS)
    {
        printf("CLIENT: failed to send message\n");
        exit(-1);
    }

    bool close = false;
    int x = 0;
    while (!close)
    {
        void* data;
        if(receive(&data,4) != NetResult::SUCSESS)
        {
            printf("CLIENT: failed to receive message\n");
            close = true;
        }
        printf("CLIENT: %s",reinterpret_cast<char*>(data));
        if(x == 5) close = true;
        x++;
    }

    if(disconnect() != NetResult::SUCSESS)
    {
        printf("CLIENT: failed to disconnect\n");
        exit(-1);
    }

    terminate();
    return 0;
}
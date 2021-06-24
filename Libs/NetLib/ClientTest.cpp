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

    char* msg = "ping";
    if(send(reinterpret_cast<void*>(msg),4) != NetResult::SUCSESS)
    {
        printf("CLIENT: failed to send message\n");
        exit(-1);
    }

    void* data;
    if(receive(&data,4) != NetResult::SUCSESS)
    {
        printf("CLIENT: failed to receive message\n");
        exit(-1);
    }

    printf("CLIENT: data returned - %s\n",data);

    if(disconnect() != NetResult::SUCSESS)
    {
        printf("CLIENT: failed to disconnect\n");
        exit(-1);
    }

    terminate();
    return 0;
}
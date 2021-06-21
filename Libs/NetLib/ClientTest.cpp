#include <Api/NetLib.h>
using namespace LunaLux::net;

int main()
{
    if(netInit() != NetResult::SUCSESS)
    {
        printf("failed to load net lib");
        exit(-1);
    }

    setNetworkType(NetworkType::CLIENT);

    if(connect("localhost:25565") != NetResult::SUCSESS)
    {
        printf("failed to connect");
        exit(-1);
    }

    const char* msg = "ping";
    if(send(reinterpret_cast<const void*>(msg), sizeof(char) * 4) != NetResult::SUCSESS)
    {
        printf("failed to send message");
        exit(-1);
    }

}
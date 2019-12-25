#include "NetworkHandler.hpp"

int main()
{
    babel::NetworkHandler network;

    network.startVoiceCommunication("127.0.0.1",
                                    42424);
    return 0;
}

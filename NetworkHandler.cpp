//
// Created by spynight on 12/25/19.
//

#include "NetworkHandler.hpp"
#include "ClientUdpMultiThreadWrapper.hpp"

void babel::NetworkHandler::startVoiceCommunication(const std::string &hostAddress,
                                                    unsigned int port)
{
    _udp.sendMessage("Hello world");
}

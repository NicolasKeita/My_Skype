//
// Created by spynight on 12/25/19.
//

#include <thread>
#include "NetworkHandler.hpp"
#include "ClientUdpMultiThreadWrapper.hpp"

void babel::NetworkHandler::startVoiceCommunication(const std::string &hostAddress,
                                                    unsigned int port)
{
    _udp.setServer(hostAddress, port);
    std::thread thread(&babel::NetworkHandler::_handleProtocolVOIP, this);
    thread.detach();
}

void babel::NetworkHandler::_handleProtocolVOIP()
{
    _udp.sendMessage("Hello world");
}
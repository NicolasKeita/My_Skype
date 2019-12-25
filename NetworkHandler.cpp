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
    _thread = std::thread(&babel::NetworkHandler::_handleProtocolVOIP, this);
}

void babel::NetworkHandler::_handleProtocolVOIP()
{
    std::string messageToSend = "Hello world !";
    while (true) {
        _udp.sendMessage(messageToSend);
    }
}

void babel::NetworkHandler::stopCurrentCommunication()
{
    _thread.join();
}
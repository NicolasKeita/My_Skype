//
// Created by spynight on 12/25/19.
//

#include <portaudio.h>
#include <thread>
#include <string>
#include "NetworkHandler.hpp"
#include "ClientUdpMultiThreadWrapper.hpp"
#include "AudioWrapper.hpp"

void babel::NetworkHandler::startVoiceCommunication(const std::string &hostAddress,
                                                    unsigned int port)
{
    _udp.setServer(hostAddress, port);

    _audio = std::make_unique<babel::AudioWrapper>(*this);
    this->_handleProtocolVOIP();
    //AudioWrapper audio(*this);
    //_thread = std::thread(&babel::NetworkHandler::_handleProtocolVOIP, this);
}

void babel::NetworkHandler::_handleProtocolVOIP()
{
   // _thread = std::thread(&babel::AudioWrapper::recordInputVoice, _audio);
    _audio->recordInputVoice();
    _audio->listenSound();
    // Sending voiceData async automatically
    //AudioWrapper audio(*this);

    //while (true) {}
}

void babel::NetworkHandler::stopCurrentCommunication()
{
    //_thread.join();
}

void babel::NetworkHandler::sendMessage(const std::string &msg, size_t msgLength)
{
    _udp.sendMessage(msg, msgLength);
}

std::string babel::NetworkHandler::getMessage()
{
    return _udp.getReply();
}
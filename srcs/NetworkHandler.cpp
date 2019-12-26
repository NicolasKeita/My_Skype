//
// Created by spynight on 12/25/19.
//

#include <portaudio.h>
#include <thread>
#include "NetworkHandler.hpp"
#include "ClientUdpMultiThreadWrapper.hpp"
#include "AudioWrapper.hpp"

void babel::NetworkHandler::startVoiceCommunication(const std::string &hostAddress,
                                                    unsigned int port)
{
    _udp.setServer(hostAddress, port);
    _thread = std::thread(&babel::NetworkHandler::_handleProtocolVOIP, this);
}

void babel::NetworkHandler::_handleProtocolVOIP()
{
    AudioWrapper audio;

    while (true) {
        audio.clearBuffer();
        std::pair<PaStream *, size_t> input_voice = audio.recordInputVoice();
        _udp.sendMessage(input_voice.first, input_voice.second);
        //auto reply = _udp.getReply();
        //audio.listenSound(reply);

    }
}

void babel::NetworkHandler::stopCurrentCommunication()
{
    _thread.join();
}
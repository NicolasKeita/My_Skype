//
// Created by spynight on 12/25/19.
//

#include <time.h>
#include <thread>
#include <vector>
#include <string>
#include "NetworkHandler.hpp"
#include "AudioWrapper.hpp"

void babel::NetworkHandler::startVoiceCommunication(const std::string &hostAddress,
                                                    unsigned int port)
{
    _udp.setServer(hostAddress, port);

    _audio = std::make_unique<babel::AudioWrapper>(*this);
    this->_handleProtocolVOIP();
}

void babel::NetworkHandler::_handleProtocolVOIP()
{
    std::thread thread([&]() {
        clock_t t = clock();
        while (true) {
            if (((float) clock() - t) / CLOCKS_PER_SEC > 0.5) {
                t = clock();
                std::vector<float> record = _audio->getRecord();
                _udp.sendMessage<std::vector<float>>(record);
            }
        }
    });
    thread.detach();

    std::thread thread2([&](){
       while (true) {
            std::vector<float> record = _udp.getReply<std::vector<float>>();
            _audio->playRecord(record);
       }
    });
    thread2.detach();
    //_audio->listenSound();
    // Sending voiceData async automatically
    //AudioWrapper audio(*this);

    //while (true) {}
}

void babel::NetworkHandler::stopCurrentCommunication()
{
    //_thread.join();
}

/*
template<class T>
void babel::NetworkHandler::sendMessage(const T &msg, size_t msgLength)
{
    _udp.sendMessage<T>(msg, msgLength);
}

template<class T>
T babel::NetworkHandler::getMessage()
{
    return _udp.getReply<T>();
}*/
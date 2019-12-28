//
// Created by spynight on 12/25/19.
//

#include <portaudio.h>
#include <thread>
#include <vector>
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
    //_audio->recordInputVoice();
    std::thread thread([&]() {
        while (true) {
            std::vector<float> record = _audio->getRecord();
            record.at(0) = 1;
            _udp.sendMessage<std::vector<float, std::allocator<float>>>(record, record.size());
            if (true)
                break;
        }
    });
    thread.detach();

    std::thread thread2([&](){
       while (true) {
            std::vector<float> record2 = _udp.getReply<std::vector<float>>();
            //exit(23);
            std::vector<float> record_cast(record2.begin(), record2.end());
            _audio->playRecord(record_cast);
            if (true)
                break;
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
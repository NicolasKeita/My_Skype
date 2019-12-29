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
    _audio->startStream();
    _audio->startRecording();
    this->_handleProtocolVOIP();
}

void babel::NetworkHandler::_handleProtocolVOIP()
{
    std::thread thread([&]() {
        if (_audio->isRecording()) {
            clock_t t = clock();
            while (true) {
                if (((float) clock() - t) / CLOCKS_PER_SEC > 0.1) { // Sending slower would create the "output underflow" error
                    t = clock();
                    std::vector<float> record = _audio->getRecord();
                    _udp.sendMessage<std::vector<float>>(record);
                }
            }
        }
    });
    thread.detach();

    std::thread thread2([&]() {
        if (_audio->isRecording()) {
            while (true) {
                std::vector<float> record = _udp.getReply<std::vector<float>>();
                _audio->playRecord(record);
            }
        }
    });
    thread2.detach();
}

void babel::NetworkHandler::stopCurrentCommunication()
{}


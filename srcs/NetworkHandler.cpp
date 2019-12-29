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
    //_udp.setServer(hostAddress, port);
    (void)hostAddress;
    (void)port;

    _audio = std::make_unique<babel::AudioWrapper>(*this);
    _audio->startStream();
    _audio->startRecording();
    this->_handleProtocolVOIP();
}

void babel::NetworkHandler::_handleProtocolVOIP()
{
    std::thread thread([&]() {
        if (_audio->isStreaming()) {
            clock_t t = clock();
            clock_t clock_resetStream = clock();
            while (true) {
                if (((float) clock() - clock_resetStream) / CLOCKS_PER_SEC > 5.0) {
                    _audio->restartStream();
                    clock_resetStream = clock();
                }
                if (_audio->isRecording() && _audio->isStreaming()) {
                    if (((float) clock() - t) / CLOCKS_PER_SEC > 0.09) { // Sending slower would create the "output underflow" error
                        t = clock();
                        std::vector<float> record = _audio->getRecord();
                        _udp.sendMessage<std::vector<float>>(record);
                    }
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
{
    _audio->closeStream();
}

int babel::NetworkHandler::tryToConnect(const std::string &hostAddress,
                                        unsigned int port)
{
    _udp.setServer(hostAddress, port);

    std::thread thread([&]()
    {
        while (true) {
            auto msgReceived = _udp.getReply<std::string>();
            if (msgReceived == "ASK_FOR_DISCUSSION") {
                _partnerFound = true;
                return;
            }
        }
    });
    thread.detach();

    clock_t t = clock();
    while (true) {
        if (((float) clock() - t) / CLOCKS_PER_SEC > 5.0) {
            t = clock();
            _udp.sendMessage<std::string>("ASK_FOR_DISCUSSION");
        }
        if (_partnerFound)
            return 0;
    }
    return 1;
}
//
// Created by spynight on 12/25/19.
//

#ifndef MY_SKYPE_NETWORKHANDLER_HPP
#define MY_SKYPE_NETWORKHANDLER_HPP

#include <thread>
#include <memory>
#include <string>
#include <ClientUdpMultiThreadWrapper.hpp>
#include "AudioWrapper.hpp"

namespace uti::network {
    class ClientUdpMultiThreadWrapper;
}

namespace babel {
    class NetworkHandler {
        public:
            NetworkHandler() : _partnerFound { false } {};

            int tryToConnect(const std::string &hostAddress,
                             unsigned int port);
            void startVoiceCommunication(const std::string &hostAddress,
                                         unsigned int port);
            void stopCurrentCommunication();

        private:
            void _handleProtocolVOIP();

        private:
            uti::network::ClientUdpMultiThreadWrapper   _udp;
            std::unique_ptr<IAudioWrapper>              _audio;
            bool                                        _partnerFound;
    };
}


#endif //MY_SKYPE_NETWORKHANDLER_HPP

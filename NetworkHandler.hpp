//
// Created by spynight on 12/25/19.
//

#ifndef MY_SKYPE_NETWORKHANDLER_HPP
#define MY_SKYPE_NETWORKHANDLER_HPP

#include <string>
#include "ClientUdpMultiThreadWrapper.hpp"

namespace babel {
    class NetworkHandler {
        public:
            NetworkHandler() = default;

            void startVoiceCommunication(const std::string &hostAddress,
                                         unsigned int port);

        private:
            void _handleProtocolVOIP();

        private:
            uti::network::ClientUdpMultiThreadWrapper _udp;
    };
}


#endif //MY_SKYPE_NETWORKHANDLER_HPP

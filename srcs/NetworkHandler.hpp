//
// Created by spynight on 12/25/19.
//

#ifndef MY_SKYPE_NETWORKHANDLER_HPP
#define MY_SKYPE_NETWORKHANDLER_HPP

#include <thread>
#include <memory>
#include <string>
#include "ClientUdpMultiThreadWrapper.hpp"
#include "AudioWrapper.hpp"

namespace babel {
    class NetworkHandler {
        public:
            NetworkHandler() = default;

            void startVoiceCommunication(const std::string &hostAddress,
                                         unsigned int port);
            void stopCurrentCommunication();

            template<class T>
            void sendMessage(const T &msg, size_t msgLength)
            {
                _udp.sendMessage<T>(msg, msgLength);
            }

            template<class T>
            T getMessage()
            {
                return _udp.getReply<T>();
            }

        private:
            void _handleProtocolVOIP();

        private:
            uti::network::ClientUdpMultiThreadWrapper   _udp;
            std::thread                                 _thread;
            std::unique_ptr<AudioWrapper>                   _audio;
    };
}


#endif //MY_SKYPE_NETWORKHANDLER_HPP

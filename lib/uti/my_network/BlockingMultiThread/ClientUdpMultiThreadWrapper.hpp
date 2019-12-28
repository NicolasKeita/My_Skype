/*
** EPITECH PROJECT, 2019
** ClientUdpMultiThreadWrapper.hpp
** File description:
**
*/

#ifndef MY_NETWORK_LIBRARY_CLIENTUDPMULTITHREADWRAPPER_HPP
#define MY_NETWORK_LIBRARY_CLIENTUDPMULTITHREADWRAPPER_HPP

#include <memory>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>
#include "IClientUdpMultiThreadWrapper.hpp"

namespace uti::network {
    class ClientUdpMultiThreadWrapper : public IClientUdpMultiThreadWrapper {
        public:
            ClientUdpMultiThreadWrapper();

            void setServer(const std::string &serverAddress, unsigned int port) override;

            template<class T>
            void sendMessage(const T & message, size_t messageLength)
            {
                if (!_serverSet) {
                    std::cerr << "[Network ClientUdpMultiThread] Where to send ? You first have to set a host" << std::endl;
                    return;
                }
                //unsigned char * message_cast = boost::any_cast<unsigned char *>(message);

                char *message_cast = "HEllo world";

                _socket->send_to(boost::asio::buffer(message_cast,
                                                     messageLength),
                                 *_endpoints.begin());
            }

            template<class T>
            T getReply()
            {
                using boost::asio::ip::udp;
                char reply[10000];
                udp::endpoint sender_endpoint;
                size_t reply_length = _socket->receive_from(
                        boost::asio::buffer(reply, 10000),
                        sender_endpoint); // blocking function
                //sender_endpoint is now equal to the server
//    return std::string(reply, reply_length);
                std::vector<float> array(10, 1);
                return array;
            };
            void stop() override;

        private:
            boost::asio::io_context                         _io_context;
            std::unique_ptr<boost::asio::ip::udp::socket>   _socket;
            boost::asio::ip::udp::resolver                  _resolver;
            boost::asio::ip::udp::resolver::results_type    _endpoints;
            std::string             _serverAddress;
            size_t                  _port;
            bool                    _serverSet;
    };
}

#endif //MY_NETWORK_LIBRARY_CLIENTUDPMULTITHREADWRAPPER_HPP

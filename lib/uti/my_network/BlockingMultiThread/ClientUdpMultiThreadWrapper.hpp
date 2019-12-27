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
            void sendMessage(const boost::any & message, size_t messageLength) override;
            std::string getReply() override;
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

/*
** EPITECH PROJECT, 2019
** ClientUdpMultiThreadWrapper.cpp
** File description:
**
*/


#include "ClientUdpMultiThreadWrapper.hpp"

using boost::asio::ip::udp;

uti::network::ClientUdpMultiThreadWrapper::ClientUdpMultiThreadWrapper()
        : _resolver { _io_context },
          _serverAddress { "-1" },
          _port { 0 },
          _serverSet { false }
{}

void uti::network::ClientUdpMultiThreadWrapper::setServer(const std::string &serverAddress,
                                                          unsigned int port)
{
    _serverAddress = serverAddress;
    _port = port;
    _socket = std::make_unique<udp::socket>(_io_context,
                                            udp::endpoint(udp::v4(), port));
    _endpoints = _resolver.resolve(udp::v4(),
                                   _serverAddress,
                                   std::to_string(_port));
    _serverSet = true;
}

void uti::network::ClientUdpMultiThreadWrapper::sendMessage(const boost::any & message, size_t messageLength)
{
    if (!_serverSet) {
        std::cerr << "[Network ClientUdpMultiThread] Where to send ? You first have to set a host" << std::endl;
        return;
    }
    std::string message_cast = boost::any_cast<std::string>(message);
    std::cout << "Messagel ength : " << messageLength << std::endl;

    _socket->send_to(boost::asio::buffer(message_cast,
                                        messageLength),
                    *_endpoints.begin());
}

//Blocking
std::string uti::network::ClientUdpMultiThreadWrapper::getReply()
{
    std::cout << "Getting reply" << std::endl;
    char reply[4000];
    udp::endpoint sender_endpoint;
    size_t reply_length = _socket->receive_from(
            boost::asio::buffer(reply, 4000),
            sender_endpoint); // blocking function
    //sender_endpoint is now equal to the server
    return std::string(reply, reply_length);
}

void uti::network::ClientUdpMultiThreadWrapper::stop()
{
    _socket->shutdown(boost::asio::ip::udp::socket::shutdown_both);
}
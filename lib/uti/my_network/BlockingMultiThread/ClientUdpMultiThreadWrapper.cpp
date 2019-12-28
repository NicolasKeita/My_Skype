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

/*
template<class T>
void uti::network::ClientUdpMultiThreadWrapper::sendMessage(const T & message, size_t messageLength)
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
}*/

//Blocking
/*
template<class T>
T uti::network::ClientUdpMultiThreadWrapper::getReply()
{
    char reply[10000];
    udp::endpoint sender_endpoint;
    size_t reply_length = _socket->receive_from(
            boost::asio::buffer(reply, 10000),
            sender_endpoint); // blocking function
    //sender_endpoint is now equal to the server
//    return std::string(reply, reply_length);
    std::vector<float> array(10, 1);
    return array;
}*/

void uti::network::ClientUdpMultiThreadWrapper::stop()
{
    _socket->shutdown(boost::asio::ip::udp::socket::shutdown_both);
}
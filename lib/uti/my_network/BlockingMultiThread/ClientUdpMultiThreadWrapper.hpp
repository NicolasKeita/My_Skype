/*
** EPITECH PROJECT, 2019
** ClientUdpMultiThreadWrapper.hpp
** File description:
**
*/

#ifndef MY_NETWORK_LIBRARY_CLIENTUDPMULTITHREADWRAPPER_HPP
#define MY_NETWORK_LIBRARY_CLIENTUDPMULTITHREADWRAPPER_HPP

#include <memory>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/serialization/vector.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/tuple/tuple.hpp>
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
                    exit(30);
                }

                // Serialization
                std::ostringstream archive_stream;
                boost::archive::text_oarchive archive(archive_stream);
                archive << message;
                std::string message_serialized = archive_stream.str();

                // Header creation
                std::ostringstream  header_stream;
                header_stream << std::setw(_header_length) \
                    << std::hex << message_serialized.size();
                if (!header_stream || header_stream.str().size() != _header_length) {
                    std::cerr << "[CLientUdpMultiThread] Serialization Object went wrong" << std::endl;
                    exit(84);
                }
                std::string header = header_stream.str();

                // Merge
                std::vector<boost::asio::const_buffer> buffers;
                buffers.push_back(boost::asio::buffer(header));
                buffers.push_back(boost::asio::buffer(message_serialized));

                _socket->send_to(buffers, *_endpoints.begin());
            }

            template<class T>
            T getReply()
            {
                using boost::asio::ip::udp;

                _socket->receive(boost::asio::buffer(inbound_header));

                std::istringstream is(std::string(inbound_header, _header_length));
                std::size_t inbound_data_size = 0;

                if (!(is >> std::hex >> inbound_data_size)) {
                    std::cerr << "[CLientUdpMultiThread] Header is not valid : " << std::dec << inbound_data_size << std::endl;
                    exit(31);
                }
                inbound_data.resize(inbound_data_size);
                _socket->receive(boost::asio::buffer(inbound_data));

                T t;
                try {
                    std::string archive_data(&inbound_data[0], inbound_data.size());
                    std::istringstream archive_stream(archive_data);
                    boost::archive::text_iarchive archive(archive_stream);
                    archive >> t;
                }
                catch (std::exception & e)
                {
                    std::cerr << "[CLientUdpMultiThread] Unable to decode data." << std::endl;
                    exit(34);
                }
                return t;
                /*
                void (ClientUdpMultiThreadWrapper::*f)(
                        const boost::system::error_code&,
                        T&, boost::tuple<Handler>)
                = &connection::handle_read_header<T, Handler>;
                boost::asio::async_read(socket_, boost::asio::buffer(inbound_header_),
                                        boost::bind(f,
                                                    this, boost::asio::placeholders::error, boost::ref(t),
                                                    boost::make_tuple(handler)));
            }

                _socket->receive_from()
                std::istringstream is(std::string())
*/
                /*
                char reply[10000];
                udp::endpoint sender_endpoint;
                size_t reply_length = _socket->receive_from(
                        boost::asio::buffer(reply, 10000),
                        sender_endpoint); // blocking function
                //sender_endpoint is now equal to the server
//    return std::string(reply, reply_length);
                std::vector<float> array(10, 1);
                return array;
                 */
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
            size_t                  _header_length;
            char                    inbound_header[8];
            std::vector<char>       inbound_data;
    };
}

#endif //MY_NETWORK_LIBRARY_CLIENTUDPMULTITHREADWRAPPER_HPP

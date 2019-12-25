/*
** EPITECH PROJECT, 2019
** IClientUdpMultiThreadWrapper.hpp
** File description:
**
*/

#ifndef MY_NETWORK_LIBRARY_ICLIENTUDPMULTITHREADWRAPPER_HPP
#define MY_NETWORK_LIBRARY_ICLIENTUDPMULTITHREADWRAPPER_HPP

#include <boost/any.hpp>

namespace uti::network {
    class IClientUdpMultiThreadWrapper {
        protected:
            virtual void setServer(const std::string &serverAddress, size_t port) = 0;
            virtual void sendMessage(const boost::any & message) = 0;
            virtual std::string getReply() = 0;
            virtual void stop() = 0;
    };
}

#endif //MY_NETWORK_LIBRARY_ICLIENTUDPMULTITHREADWRAPPER_HPP

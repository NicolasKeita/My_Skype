/*
** EPITECH PROJECT, 2019
** IGraphicWrapper.hpp
** File description:
**
*/

#ifndef MY_BABEL_IGRAPHICWRAPPER_HPP
#define MY_BABEL_IGRAPHICWRAPPER_HPP

#include <cstddef>

namespace babel::graphic {
    class IGraphicWrapper {
        public:
            virtual void setWindowSize(std::size_t width, std::size_t height) = 0;
            virtual void createHomePage() = 0;
            virtual void createPhoneCallPage() = 0;
            virtual void deletePage() = 0;
            virtual void showPage() = 0;

    };
}

#endif //MY_BABEL_IGRAPHICWRAPPER_HPP

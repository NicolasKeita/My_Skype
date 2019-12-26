/*
** EPITECH PROJECT, 2019
** GraphicWrapper.hpp
** File description:
**
*/

#ifndef MY_BABEL_GRAPHICWRAPPER_HPP
#define MY_BABEL_GRAPHICWRAPPER_HPP

#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include "IGraphicWrapper.hpp"
#include "ClientUdpMultiThreadWrapper.hpp"

namespace babel::graphic {
    class GraphicWrapper : public QDialog, public IGraphicWrapper {
        public:
            GraphicWrapper(QApplication &app);

            void setWindowSize(std::size_t width, std::size_t height);
            void createHomePage();
            void createPhoneCallPage();
            void deletePage();
            void showPage();

        private:
            void sound_test(); // TODO : remove
            QApplication        &_app;
            QWidget         _window;
            //babel::network::ClientWrapper   network;
    };
}


#endif //MY_BABEL_GRAPHICWRAPPER_HPP

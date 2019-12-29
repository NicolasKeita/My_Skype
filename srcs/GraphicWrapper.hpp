/*
** EPITECH PROJECT, 2019
** GraphicWrapper.hpp
** File description:
**
*/

#ifndef MY_BABEL_GRAPHICWRAPPER_HPP
#define MY_BABEL_GRAPHICWRAPPER_HPP

#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QDialog>
#include "IGraphicWrapper.hpp"
#include "ClientUdpMultiThreadWrapper.hpp"

namespace babel::graphic {
    class GraphicWrapper : public QDialog, public IGraphicWrapper {
        public:
            explicit GraphicWrapper(QApplication &app);

            void setWindowSize(std::size_t width, std::size_t height) override;
            void createHomePage() override;
            void createPhoneCallPage() override;
            void deletePage() override;
            void showPage() override;

        private:
            QApplication    &_app;
            QWidget         _window;
            QPushButton     button;
    };
}


#endif //MY_BABEL_GRAPHICWRAPPER_HPP

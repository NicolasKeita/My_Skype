/*
** EPITECH PROJECT, 2019
** GraphicWrapperSub.cpp
** File description:
**
*/

#include <QtGui/QFontDatabase>
#include <QtWidgets/QAbstractButton>
#include "GraphicWrapper.hpp"
#include "Macro.hpp"

babel::graphic::GraphicWrapper::GraphicWrapper(QApplication &app)
        : _app{ app },
          button { "", &_window }
{
    QIcon icon(GREEN_PHONE);
    button.setIcon(icon);
    button.setGeometry(WIDTH_WIN / 2, HEIGHT_WIN / 2, 100, 100);
    button.setIconSize(QSize(100, 100));

    /*
    QObject::connect(&button, &QAbstractButton::clicked,
                     this, &babel::graphic::GraphicWrapper::sound_test);
    */
}

void babel::graphic::GraphicWrapper::setWindowSize(std::size_t width,
                                                   std::size_t height)
{
    _window.setFixedSize(width, height);
}

void babel::graphic::GraphicWrapper::createHomePage()
{}

void babel::graphic::GraphicWrapper::createPhoneCallPage()
{}

void babel::graphic::GraphicWrapper::deletePage()
{}

void babel::graphic::GraphicWrapper::showPage()
{
    _window.show();
}


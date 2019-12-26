#include <QtWidgets/QApplication>
#include "GraphicWrapper.hpp"
#include "NetworkHandler.hpp"

int main(int argc, char *argv[])
{
    babel::NetworkHandler   network;
    network.startVoiceCommunication("127.0.0.1",
                                    42424);

    // Graphic
    QApplication                    app(argc, argv);
    babel::graphic::GraphicWrapper  clientWrapper(app);

    clientWrapper.setWindowSize(1920, 1080);
    clientWrapper.createHomePage();
    clientWrapper.showPage();
    //QApplication::exec();
    app.exec();

    network.stopCurrentCommunication();
    return 0;
}

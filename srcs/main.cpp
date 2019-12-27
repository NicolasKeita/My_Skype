#include <QtWidgets/QApplication>
#include "GraphicWrapper.hpp"
#include "NetworkHandler.hpp"
#include "Macro.hpp"

int main(int argc, char *argv[])
{
    babel::NetworkHandler   network;
    network.startVoiceCommunication("0.0.0.0",
                                    std::stoi(argv[1]));

    // Graphic
    QApplication                    app(argc, argv);
    babel::graphic::GraphicWrapper  clientWrapper(app);

    clientWrapper.setWindowSize(WIDTH_WIN, HEIGHT_WIN);
    clientWrapper.createHomePage();
    clientWrapper.showPage();
    //QApplication::exec();
    app.exec();

    network.stopCurrentCommunication();
    return 0;
}

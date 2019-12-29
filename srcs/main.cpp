#include <QtWidgets/QApplication>
#include "GraphicWrapper.hpp"
#include "NetworkHandler.hpp"
#include "Macro.hpp"
#include "MyProgArgs.hpp"

void startVoiceCommunication(babel::NetworkHandler &network,
                             const uti::MyProgArgs &args)
{
    unsigned int    port = 42424;
    std::string     serverAddress = "0.0.0.0";

    if (args.getSize() > 2) {
        try {
            port = std::stoi(args.getArgs().at(2));
            if (port < 2000)
                throw std::invalid_argument("Pick higher port");
            serverAddress = args.getArgs().at(1);
        }
        catch (std::invalid_argument &e) {
            std::cerr << "Wrong port\n" << e.what() << std::endl;
            exit(84);
        }
    }
    network.startVoiceCommunication(serverAddress, port);
}

int main(int argc, char *argv[], char **env)
{
    uti::MyProgArgs args(argc, argv, env, 0);
    babel::NetworkHandler   network;

    startVoiceCommunication(network, args);

    // Graphic
    QApplication                    app(argc, argv);
    babel::graphic::GraphicWrapper  clientWrapper(app);

    clientWrapper.setWindowSize(WIDTH_WIN, HEIGHT_WIN);
    clientWrapper.createHomePage();
    clientWrapper.showPage();
    QApplication::exec();

    network.stopCurrentCommunication();
    return 0;
}

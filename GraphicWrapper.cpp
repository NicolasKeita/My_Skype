/*
** EPITECH PROJECT, 2019
** GraphicWrapperSub.cpp
** File description:
**
*/

#include "GraphicWrapper.hpp"
#include "Macro.hpp"
#include "Exception.hpp"

babel::graphic::GraphicWrapper::GraphicWrapper(QApplication &app)
        : _app{ app }
{}

void babel::graphic::GraphicWrapper::setWindowSize(std::size_t width,
                                                   std::size_t height)
{
    _window.setFixedSize(width, height);
}

void babel::graphic::GraphicWrapper::createHomePage()
{
    int id = QFontDatabase::addApplicationFont(BASIC_FONT);
    if (id == -1)
        throw CannotLoadResource(BASIC_FONT);
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont font(family, 10);
    _app.setFont(font);
    auto *button = new QPushButton("", &_window);
    QIcon icon(GREEN_PHONE);
    button->setIcon(icon);
    button->setGeometry(WIDTH_WIN / 2, HEIGHT_WIN / 2, 100, 100);
    button->setIconSize(QSize(100, 100));

    //Quand le bouton est appuyé, soundDemonstration() est appelé
    QObject::connect(button, &QAbstractButton::clicked,
            this, &babel::graphic::GraphicWrapper::sound_test);
    QObject::connect(button, &QAbstractButton::clicked,
                     this, &babel::graphic::GraphicWrapper::sound_test);
//    clientNetwork.connectToHost("0.0.0.0", 42424, &handleMessageReceived);
}

void babel::graphic::GraphicWrapper::createPhoneCallPage()
{

}

void babel::graphic::GraphicWrapper::deletePage()
{
    //_window.clear();
}



void babel::graphic::GraphicWrapper::showPage()
{
    _window.show();
}

// TODO : remove the folloowing


#include <iostream>
#include <portaudio.h>

static const int SAMPLE_RATE = 44100;
#define FRAMES_PER_BUFFER	1024
#define LATENCY_CONSTANT	10
#define NUM_CHANNELS		2
#define FRAME_SIZE			960

std::string handleMessageReceived(const std::string &msgReceived);

void babel::graphic::GraphicWrapper::sound_test()
{
    auto err = Pa_Initialize();
    if (err != paNoError)
    {
        std::cerr << "Error: Initialization failed: " << Pa_GetErrorText(err) << std::endl;
        exit(43);
    } else {
        std::cout << "everything is good " << std::endl;
        PaStreamParameters inputParameters;
        PaStreamParameters outputParameters;

        if ((inputParameters.device = Pa_GetDefaultInputDevice()) == paNoDevice) {
            std::cerr << "Error: No default input device." << std::endl;
            exit(64);
        }
        inputParameters.channelCount = NUM_CHANNELS;
        inputParameters.sampleFormat = paFloat32;
        inputParameters.suggestedLatency =
                LATENCY_CONSTANT * Pa_GetDeviceInfo(inputParameters.device)->defaultLowInputLatency;
        inputParameters.hostApiSpecificStreamInfo = nullptr;

        if ((outputParameters.device = Pa_GetDefaultOutputDevice()) == paNoDevice) {
            std::cerr << "Error: No default output device." << std::endl;
            exit(67);
        }
        outputParameters.channelCount = NUM_CHANNELS;
        outputParameters.sampleFormat = paFloat32;
        outputParameters.suggestedLatency =
                LATENCY_CONSTANT * Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency;
        outputParameters.hostApiSpecificStreamInfo = nullptr;

        PaStream *stream = nullptr;
        err = Pa_OpenStream(&stream, &inputParameters, &outputParameters, SAMPLE_RATE, FRAMES_PER_BUFFER, paClipOff,
                            nullptr, nullptr);
        if (err != paNoError) {
            std::cerr << "Error: An error occured when opening the stream." << std::endl;
            exit(66);
        } else {
            std::cout << "stream OPEN, all good" << std::endl;
        }
        if ((err = Pa_StartStream(stream)) != paNoError) {
            std::cerr << "Error: An error occured when starting the stream." << std::endl;
            exit(56);
        }

        std::vector<float> buffer(FRAME_SIZE);

        if ((err = Pa_IsStreamActive(stream)) != 1) {
            std::cerr << "Error: Can't run the stream: Stream inactive." << std::endl;
            exit(70);
        }

        while (true) {
            if ((err = Pa_ReadStream(stream, buffer.data(), FRAME_SIZE / NUM_CHANNELS)) != paNoError) {
                std::cerr << "Error: An error occured when recording stream: " << Pa_GetErrorText(err) << std::endl;
                exit(68);
            }
            if ((err = Pa_WriteStream(stream, buffer.data(), FRAME_SIZE / NUM_CHANNELS)) != paNoError) {
                std::cerr << "Error: An error occured when reading stream: " << Pa_GetErrorText(err) << std::endl;
                exit(43);
            }
        }
    }
}
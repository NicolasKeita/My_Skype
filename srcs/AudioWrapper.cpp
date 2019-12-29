//
// Created by spynight on 12/26/19.
//

#include <cstdlib>
#include <vector>
#include "AudioWrapper.hpp"
#include "NetworkHandler.hpp"

babel::AudioWrapper::AudioWrapper(NetworkHandler &network)
        : _stream { nullptr },
          network { network },
          _streaming { false },
          _recording { false },
          _bufferSize { 3600 },
          _sampleRate { 44100 }
{
    PaError paErr;
    paErr = Pa_Initialize();
    if (paErr != paNoError) {
        std::cerr << "[AudioWrapper.cpp constructor()] " \
            << Pa_GetErrorText(paErr) << std::endl;
        exit(1);
    }
}

void babel::AudioWrapper::playRecord(std::vector<SAMPLE> record)
{
    PaError paErr;
    long streamWriteAvailable = 0;

    while (streamWriteAvailable < static_cast<long>(record.size())) {
        streamWriteAvailable = Pa_GetStreamWriteAvailable(_stream);
        record.resize(streamWriteAvailable, SAMPLE_SILENCE);
        paErr = Pa_WriteStream(_stream,
                               record.data(),
                               streamWriteAvailable);
        if (paErr != paNoError) {
            std::cerr << "[AudioWRapper Playrecord()] " << Pa_GetErrorText(paErr) << std::endl;
            this->restartStream();
        }
    }
}

void babel::AudioWrapper::restartStream()
{
    closeStream();
    startStream();
    startRecording();
}

void babel::AudioWrapper::startStream()
{
    PaError paErr = Pa_OpenDefaultStream(
            &_stream,
            1,
            1, paFloat32, _sampleRate,
            _bufferSize, nullptr, nullptr);
    if (paErr != paNoError) {
        std::cerr << "[AudioWrapper startStream()] unable to startstream " \
            << Pa_GetErrorText(paErr) << std::endl;
        exit(6);
    }
    _streaming = true;
}

void babel::AudioWrapper::closeStream()
{
    if (_recording)
        stopRecording();
    if (_streaming)
        stopStream();
}

void babel::AudioWrapper::stopStream()
{
    PaError paErr = Pa_CloseStream(_stream);
    if (paErr != paNoError) {
        std::cerr << Pa_GetErrorText(paErr) << std::endl;
        exit(6);
    }
    _streaming = false;
}

void babel::AudioWrapper::stopRecording()
{
    PaError paErr = Pa_StopStream(_stream);
    if (paErr != paNoError) {
        std::cerr << Pa_GetErrorText(paErr) << std::endl;
        exit(6);
    }
    _recording = false;
}

void babel::AudioWrapper::startRecording()
{
    PaError paErr = Pa_StartStream(_stream);
    if (paErr != paNoError) {
        std::cerr << Pa_GetErrorText(paErr) << std::endl;
        exit(6);
    }
    _recording = true;
}

std::vector<SAMPLE> babel::AudioWrapper::getRecord()
{
    PaError paErr;
    long streamReadAvailable = Pa_GetStreamReadAvailable(_stream);
    std::vector<SAMPLE> record(_bufferSize, SAMPLE_SILENCE);
    if (streamReadAvailable < (long)_bufferSize) {
        paErr = Pa_ReadStream(_stream,
                              record.data(),
                              streamReadAvailable);
        if (paErr != paNoError)
            std::cerr << "[AudioWrapper, getRecord() 1] Error on ReadStream" << Pa_GetErrorText(paErr) << std::endl;
    } else {
        paErr = Pa_ReadStream(_stream,
                              record.data(),
                              _bufferSize);
        if (paErr != paNoError) {
            std::cerr << "[AudioWrapper, getRecord() 2] Error on ReadStream" << Pa_GetErrorText(paErr) << std::endl;
            restartStream();
        }
    }
    record.shrink_to_fit();
    return record;
}

bool babel::AudioWrapper::isRecording()
{
    return _recording;
}

bool babel::AudioWrapper::isStreaming()
{
    return _streaming;
}
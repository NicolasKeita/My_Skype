//
// Created by spynight on 12/26/19.
//

#include <boost/any.hpp>
#include <cstdlib>
#include "AudioWrapper.hpp"

babel::AudioWrapper::AudioWrapper()
        : _stream { nullptr },
        _sampleBlock { nullptr }
{
    _data.maxFrameIndex = NUM_SECONDS * SAMPLE_RATE;
    _totalFrames = NUM_SECONDS * SAMPLE_RATE;
    _numSamples = _totalFrames * NUM_CHANNELS;
    _numBytes = _numSamples * sizeof(SAMPLE);
    _data.recordedSamples = (SAMPLE *)calloc(_numBytes, 1);

    _err = Pa_Initialize();
    if (_err != paNoError)
        exit(1);
    _inputParameters.device = Pa_GetDefaultInputDevice();
    _inputInfo = Pa_GetDeviceInfo(_inputParameters.device);

    _outputParameters.device = Pa_GetDefaultOutputDevice();
    _outputInfo = Pa_GetDeviceInfo(_outputParameters.device);

    _numChannels = _inputInfo->maxInputChannels < _outputInfo->maxOutputChannels ? \
        _inputInfo->maxInputChannels : _outputInfo->maxOutputChannels;

    _inputParameters.channelCount = _numChannels;
    _inputParameters.sampleFormat = PA_SAMPLE_TYPE;
    _inputParameters.suggestedLatency = _inputInfo->defaultHighInputLatency;
    _inputParameters.hostApiSpecificStreamInfo = nullptr;

    _outputParameters.channelCount = _numChannels;
    _outputParameters.sampleFormat = PA_SAMPLE_TYPE;
    _outputParameters.suggestedLatency = _outputInfo->defaultHighInputLatency;
    _outputParameters.hostApiSpecificStreamInfo = nullptr;

    _err = Pa_OpenStream(&_stream,
                         &_inputParameters,
                         nullptr,
                         SAMPLE_RATE,
                         FRAMES_PER_BUFFER,
                         paClipOff,
                         //recordCallback,
                         nullptr,
                         &_data);
    if( _err != paNoError )
        exit(1);
}

boost::any babel::AudioWrapper::recordInputVoice()
{

}

void babel::AudioWrapper::listenSound(const boost::any &reply)
{

}
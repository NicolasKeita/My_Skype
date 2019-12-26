//
// Created by spynight on 12/26/19.
//

#include <boost/any.hpp>
#include <cstdlib>
#include "AudioWrapper.hpp"

static int recordCallback( const void *inputBuffer, void *outputBuffer,
                            unsigned long framesPerBuffer,
                            const PaStreamCallbackTimeInfo* timeInfo,
                            PaStreamCallbackFlags statusFlags,
                            void *userData )
 {
     auto *data = (babel::NetworkHandler *)userData;
     const auto *rptr = (const SAMPLE*)inputBuffer;

     (void) outputBuffer; /* Prevent unused variable warnings. */
     (void) timeInfo;
     (void) statusFlags;
     (void) userData;

     std::vector<SAMPLE> dataToSend(framesPerBuffer * NUM_CHANNELS, SAMPLE_SILENCE);
     if (!inputBuffer)
     {
         for(unsigned long i = 0; i < framesPerBuffer; ++i)
         {
            dataToSend.push_back(SAMPLE_SILENCE);
            if (NUM_CHANNELS == 2)
                dataToSend.push_back(SAMPLE_SILENCE);
         }
     }
     else
     {
         dataToSend.insert(dataToSend.end(), rptr, rptr + framesPerBuffer * NUM_CHANNELS);
         if (NUM_CHANNELS == 2)
             dataToSend.insert(dataToSend.end(), rptr, rptr + framesPerBuffer * NUM_CHANNELS);
     }
     data->sendMessage(std::string(dataToSend.begin(), dataToSend.end()));
     return paContinue;
 }

babel::AudioWrapper::AudioWrapper(NetworkHandler &network)
        : _stream { nullptr },
        _sampleBlock { nullptr }
{
    _dataMyVoice.maxFrameIndex = NUM_SECONDS * SAMPLE_RATE;
    _totalFrames = NUM_SECONDS * SAMPLE_RATE;
    _numSamples = _totalFrames * NUM_CHANNELS;
    _numBytes = _numSamples * sizeof(SAMPLE);
    _dataMyVoice.recordedSamples = (SAMPLE *)calloc(_numBytes, 1);

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
                         recordCallback,
                         &network);
    if( _err != paNoError )
        exit(1);
    _err = Pa_StartStream(_stream);
    if (_err != paNoError)
        exit(1);
    /*
    while((_err = Pa_IsStreamActive(_stream)) == 1) {
//        Pa_Sleep(1000);

        printf("index = %d\n", _dataMyVoice.frameIndex ); fflush(stdout);
        _dataMyVoice.frameIndex = 0;
        std::fill(_dataMyVoice.recordedSamples, _dataMyVoice.recordedSamples + _numBytes, 0);
        //memset(_dataMyVoice.recordedSamples, 0, _numBytes * sizeof(*_dataMyVoice.recordedSamples));
    }*/
}

std::pair<PaStream *,size_t> babel::AudioWrapper::recordInputVoice()
{
    return std::pair<PaStream *,size_t>(_stream, 10000);
    SAMPLE *copySample = _dataMyVoice.recordedSamples = (SAMPLE *)calloc(_numBytes, 1);
    std::copy(_dataMyVoice.recordedSamples, _dataMyVoice.recordedSamples + _numBytes, copySample);
    std::pair<unsigned char *, size_t> newSample(copySample, _dataMyVoice.frameIndex);
    return newSample;
}

void babel::AudioWrapper::listenSound(const boost::any &reply)
{

}

void babel::AudioWrapper::clearBuffer()
{
    std::fill(_dataMyVoice.recordedSamples, _dataMyVoice.recordedSamples + _numBytes, 0);
    _dataMyVoice.frameIndex = 0;
}
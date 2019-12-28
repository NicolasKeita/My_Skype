//
// Created by spynight on 12/26/19.
//

#include <boost/any.hpp>
#include <cstdlib>
#include <time.h>
#include "AudioWrapper.hpp"
#include "NetworkHandler.hpp"

static int playCallback( const void *inputBuffer, void *outputBuffer,
                           unsigned long framesPerBuffer,
                           const PaStreamCallbackTimeInfo* timeInfo,
                           PaStreamCallbackFlags statusFlags,
                           void *userData )
{
    /*
    (void) inputBuffer;
    (void) timeInfo;
    (void) statusFlags;

    auto *network = (babel::NetworkHandler *)userData;
    const auto *outPtr = (const SAMPLE*)outputBuffer;

    // TODO
   auto r = network->getMessage();
   _err = Pa_WriteStream(_streamTheirVoice, )
           */
}

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

     /*
     std::vector<SAMPLE> dataToSend(framesPerBuffer * NUM_CHANNELS, SAMPLE_SILENCE);
     if (!inputBuffer)
     {
         for(unsigned long i = 0; i < framesPerBuffer * NUM_CHANNELS; ++i)
         {
            dataToSend.push_back(SAMPLE_SILENCE);
            //if (NUM_CHANNELS == 2)
            //    dataToSend.push_back(SAMPLE_SILENCE);
         }
     }
     else
     {
         dataToSend.insert(dataToSend.end(), rptr, rptr + framesPerBuffer * NUM_CHANNELS);
         //if (NUM_CHANNELS == 2)
         //    dataToSend.insert(dataToSend.end(), rptr, rptr + framesPerBuffer * NUM_CHANNELS);
     }
     //std::cerr << "Callback called" << std::endl;
     data->sendMessage(std::string(dataToSend.begin(), dataToSend.end()));
      */
     return paContinue;
 }

babel::AudioWrapper::AudioWrapper(NetworkHandler &network)
        : _inputParameters { 0, 0, 0, 0, nullptr },
          _outputParameters { 0, 0, 0, 0, nullptr },
          _streamMyVoice { nullptr },
          _streamTheirVoice { nullptr },
          _sampleBlock { nullptr },
          _i { 0 },
          max( 0 ),
          val { 0 },
          average { 0.0f },
          network { network },
          _streaming { false },
          _recording { false },
          _channel(1),
          _bufferSize(480),
          _sampleRate(48000)
{
    // maxFrameIndex = NUM_SECONDS * SAMPLE_RATE;
    _totalFrames = NUM_SECONDS * SAMPLE_RATE;
    _numSamples = _totalFrames * NUM_CHANNELS;
    _numBytes = _numSamples * sizeof(SAMPLE);
    //_dataMyVoice.recordedSamples = (SAMPLE *)calloc(_numBytes, 1);

    _err = Pa_Initialize();
    if (_err != paNoError) {
        std::cerr << Pa_GetErrorText(_err) << std::endl;
        exit(1);
    }
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
//    _outputParameters.suggestedLatency = _outputInfo->defaultLowOutputLatency;
    _outputParameters.suggestedLatency = _outputInfo->defaultHighOutputLatency;
    _outputParameters.hostApiSpecificStreamInfo = nullptr;

    _err = Pa_OpenStream(&_streamMyVoice,
                         &_inputParameters,
                         nullptr,
                         SAMPLE_RATE,
                         FRAMES_PER_BUFFER,
                         paClipOff,
                         nullptr,
                         &network);
    if( _err != paNoError )
        exit(2);
    _err = Pa_OpenStream(&_streamTheirVoice,
                         nullptr,
                         &_outputParameters,
                         SAMPLE_RATE,
                         FRAMES_PER_BUFFER,
                         paClipOff,
                         nullptr,
                         &network);
    if( _err != paNoError )
        exit(3);
}


#include <thread>

std::pair<PaStream *,size_t> babel::AudioWrapper::recordInputVoice()
{
    /*
    _err = Pa_StartStream(_streamMyVoice);
    if (_err != paNoError) {
        std::cerr << Pa_GetErrorText(_err) << std::endl;
        exit(5);
    }

    std::thread thread([&]() {
        clock_t t = clock();
        std::mutex mutex;
        std::vector<float> buffer(FRAMES_PER_BUFFER, 0);
        while (Pa_IsStreamActive(_streamMyVoice)) {
//            t = clock() - t;
            if (((float) clock() - t) / CLOCKS_PER_SEC > 1) {
                t = clock();
                mutex.lock();
//            if (Pa_GetStreamReadAvailable(_streamTheirVoice) >= 0) {
                _err = Pa_ReadStream(_streamMyVoice, buffer.data(), FRAMES_PER_BUFFER);
                if (_err != paNoError) {
                    std::cerr << Pa_GetErrorText(_err) << std::endl;
                    exit(7);
                }
                network.sendMessage<std::vector<float>>(buffer, FRAMES_PER_BUFFER);
            }
            mutex.unlock();
        }
    });
    thread.detach();
     */
}

void babel::AudioWrapper::listenSound()
{
    /*
    _err = Pa_StartStream(_streamTheirVoice);
    if (_err != paNoError) {
        std::cerr << Pa_GetErrorText(_err) << std::endl;
        exit(6);
    }

    std::thread thread([&]() {
        clock_t t = clock();
        std::vector<float> buffer(FRAMES_PER_BUFFER * 1000);
        std::mutex mutex;
        while (Pa_IsStreamActive(_streamTheirVoice)) {
            if (((float) clock() - t) / CLOCKS_PER_SEC > 1) {
                t = clock();
                mutex.lock();
                std::vector<float> msg = network.getMessage<std::vector<float>>();
                _err = Pa_WriteStream(_streamTheirVoice, msg.data(), 10);
                if (_err != paNoError) {
                    std::cerr << Pa_GetErrorText(_err) << std::endl;
                    exit(8);
                }
                mutex.unlock();
            }
        }
    });
    thread.detach();
     */
}

void babel::AudioWrapper::playRecord(std::vector<float> &record)
{
    PaError paErr;
    long streamWriteAvailable = 0;
    while (streamWriteAvailable < (long)record.size()) {
        streamWriteAvailable = Pa_GetStreamReadAvailable(_streamMyVoice);
        //while (Pa_GetStreamWriteAvailable(_streamMyVoice) < (long)record.size());
        paErr = Pa_WriteStream(_streamMyVoice, record.data(),
                               (unsigned long) record.size());
        if (paErr != paNoError)
            this->restartStream();
    }
}

void babel::AudioWrapper::clearBuffer()
{
    _err = Pa_StartStream(_streamTheirVoice);
    if (_err != paNoError)
        exit(1);
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
            &_streamMyVoice,
            _channel,
            _channel, paFloat32, SAMPLE_RATE,
            FRAMES_PER_BUFFER, nullptr, nullptr);
    if (paErr != paNoError) {
        std::cerr << Pa_GetErrorText(paErr) << std::endl;
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
    PaError paErr = Pa_CloseStream(_streamMyVoice);
    if (paErr != paNoError) {
        std::cerr << Pa_GetErrorText(paErr) << std::endl;
        exit(6);
    }
    _streaming = false;
}

void babel::AudioWrapper::stopRecording()
{
    PaError paErr = Pa_StopStream(_streamMyVoice);
    if (paErr != paNoError) {
        std::cerr << Pa_GetErrorText(paErr) << std::endl;
        exit(6);
    }
    _recording = false;
}

void babel::AudioWrapper::startRecording()
{
    PaError paErr = Pa_StartStream(_streamMyVoice);
    if (paErr != paNoError) {
        std::cerr << Pa_GetErrorText(paErr) << std::endl;
        exit(6);
    }
    _recording = true;
}

std::vector<float> babel::AudioWrapper::getRecord()
{
    PaError paErr;
    long streamReadAvailable = Pa_GetStreamReadAvailable(_streamMyVoice);
    std::vector<float> record(FRAMES_PER_BUFFER);
    if (streamReadAvailable < (long)FRAMES_PER_BUFFER)
        paErr = Pa_ReadStream(
                _streamMyVoice, record.data(),
                (unsigned long)streamReadAvailable);
    else
        paErr = Pa_ReadStream(_streamMyVoice, record.data(), FRAMES_PER_BUFFER);
    if (paErr != paNoError)
        restartStream();
    return record;
}

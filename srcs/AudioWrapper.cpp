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
     paTestData *data = (paTestData*)userData;
     const SAMPLE *rptr = (const SAMPLE*)inputBuffer;
     SAMPLE *wptr = &data->recordedSamples[data->frameIndex * NUM_CHANNELS];
     long framesToCalc;
     long i;
     int finished;
     unsigned long framesLeft = data->maxFrameIndex - data->frameIndex;

     (void) outputBuffer; /* Prevent unused variable warnings. */
     (void) timeInfo;
     (void) statusFlags;
     (void) userData;

     if( framesLeft < framesPerBuffer )
     {
         framesToCalc = framesLeft;
         finished = paComplete;
     }
     else
     {
         framesToCalc = framesPerBuffer;
         finished = paContinue;
     }

     if( inputBuffer == NULL )
     {
         for( i=0; i<framesToCalc; i++ )
         {
             *wptr++ = SAMPLE_SILENCE;  /* left */
             if( NUM_CHANNELS == 2 ) *wptr++ = SAMPLE_SILENCE;  /* right */
         }
     }
     else
     {
         for( i=0; i<framesToCalc; i++ )
         {
             *wptr++ = *rptr++;  /* left */
             if( NUM_CHANNELS == 2 ) *wptr++ = *rptr++;  /* right */
         }
     }
     data->frameIndex += framesToCalc;
     return finished;

}

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
                         recordCallback,
                         &_data);
    if( _err != paNoError )
        exit(1);
    _err = Pa_StartStream(_stream);
    if (_err != paNoError)
        exit(1);
    /*
    while((_err = Pa_IsStreamActive(_stream)) == 1) {
//        Pa_Sleep(1000);

        printf("index = %d\n", _data.frameIndex ); fflush(stdout);
        _data.frameIndex = 0;
        std::fill(_data.recordedSamples, _data.recordedSamples + _numBytes, 0);
        //memset(_data.recordedSamples, 0, _numBytes * sizeof(*_data.recordedSamples));
    }*/
}

std::pair<PaStream *,size_t> babel::AudioWrapper::recordInputVoice()
{
    return std::pair<PaStream *,size_t>(_stream, 10000);
    SAMPLE *copySample = _data.recordedSamples = (SAMPLE *)calloc(_numBytes, 1);
    std::copy(_data.recordedSamples, _data.recordedSamples + _numBytes, copySample);
    std::pair<unsigned char *, size_t> newSample(copySample, _data.frameIndex);
    return newSample;
}

void babel::AudioWrapper::listenSound(const boost::any &reply)
{

}

void babel::AudioWrapper::clearBuffer()
{
    std::fill(_data.recordedSamples, _data.recordedSamples + _numBytes, 0);
    _data.frameIndex = 0;
}
//
// Created by spynight on 12/26/19.
//

#ifndef MY_SKYPE_AUDIOWRAPPER_HPP
#define MY_SKYPE_AUDIOWRAPPER_HPP

#include <boost/any.hpp>
#include "portaudio.h"

#define PA_SAMPLE_TYPE  paFloat32
#define PRINTF_S_FORMAT "%.8f"
using SAMPLE = unsigned char;
//using SAMPLE = float;
#define NUM_CHANNELS (2)
#define SAMPLE_SILENCE (0.0f)

namespace babel {
    class NetworkHandler;
    class AudioWrapper {
        public:
            explicit AudioWrapper(NetworkHandler &network);

            std::pair<PaStream *,size_t> recordInputVoice();
            void listenSound();
            void playRecord(std::vector<unsigned char> &record);
            void clearBuffer();
            void restartStream();
            void startStream();
            void closeStream();
            void stopStream();
            void stopRecording();
            void startRecording();
            std::vector<unsigned char> getRecord();

        private:
            PaStreamParameters _inputParameters;
            PaStreamParameters _outputParameters;
            PaStream            *_streamMyVoice;
            PaStream            *_streamTheirVoice;
            PaError             _err;
            const PaDeviceInfo  *_inputInfo;
            const PaDeviceInfo  *_outputInfo;
            char                *_sampleBlock;
            int                 _i;
            unsigned int        _numBytes;
            int                 _numChannels;
            unsigned int        _numSamples;
            int                 _totalFrames;
            SAMPLE              max;
            SAMPLE              val;
            double              average;
            NetworkHandler      &network;
            bool                _streaming;
            bool _recording;
            uint32_t            _channel;
            uint32_t            _bufferSize;
            uint32_t            _sampleRate;

        public:
            static constexpr int SAMPLE_RATE = 44100;
            static constexpr int FRAMES_PER_BUFFER = 1024;
            static constexpr int NUM_SECONDS = 10; // Temps du recording
            static constexpr int DITHER_FLAG = 0;

            //static constexpr int SAMPLE_SIZE = 4;
    };
}


#endif //MY_SKYPE_AUDIOWRAPPER_HPP

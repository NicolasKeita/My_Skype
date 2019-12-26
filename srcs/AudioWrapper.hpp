//
// Created by spynight on 12/26/19.
//

#ifndef MY_SKYPE_AUDIOWRAPPER_HPP
#define MY_SKYPE_AUDIOWRAPPER_HPP

#include <boost/any.hpp>
#include "portaudio.h"
#include "NetworkHandler.hpp"

#define PA_SAMPLE_TYPE  paFloat32
#define PRINTF_S_FORMAT "%.8f"
using SAMPLE = unsigned char;
#define NUM_CHANNELS (2)
#define SAMPLE_SILENCE (0.0f)

typedef struct
{
    int     frameIndex;
    int     maxFrameIndex;
    SAMPLE  *recordedSamples;
} paTestData;

namespace babel {
    class AudioWrapper {
        public:
            AudioWrapper(NetworkHandler &network);

            //std::pair<unsigned char *, size_t> recordInputVoice();
            std::pair<PaStream *,size_t> recordInputVoice();
            void listenSound(const boost::any &reply);
            void clearBuffer();

        private:
            PaStreamParameters _inputParameters;
            PaStreamParameters _outputParameters;
            PaStream            *_stream;
            PaError             _err;
            const PaDeviceInfo  *_inputInfo;
            const PaDeviceInfo  *_outputInfo;
            char                *_sampleBlock;
            int                 _i;
            unsigned int        _numBytes;
            int                 _numChannels;
            unsigned int        _numSamples;
            paTestData          _dataMyVoice;
            paTestData          _dataTheirVoice;
            int                 _totalFrames;
            SAMPLE              max;
            SAMPLE              val;
            double              average;

        public:
            static constexpr int SAMPLE_RATE = 44100;
            static constexpr int FRAMES_PER_BUFFER = 512;
            static constexpr int NUM_SECONDS = 10; // Temps du recording
            static constexpr int DITHER_FLAG = 0;

            static constexpr int SAMPLE_SIZE = 4;
    };
}


#endif //MY_SKYPE_AUDIOWRAPPER_HPP

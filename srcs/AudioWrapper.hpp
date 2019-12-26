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

typedef struct
{
    SAMPLE  *recordedSamples;
    int     frameIndex;
    int     maxFrameIndex;
} paTestData;

namespace babel {
    class AudioWrapper {
        public:
            AudioWrapper();

            boost::any recordInputVoice();
            void listenSound(const boost::any &reply);

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
            paTestData          _data;
            int                 _totalFrames;
            SAMPLE              max;
            SAMPLE              val;
            double              average;

        public:
            static constexpr int SAMPLE_RATE = 44100;
            static constexpr int FRAMES_PER_BUFFER = 512;
            static constexpr int NUM_SECONDS = 5;
            static constexpr int NUM_CHANNELS = 2;
            static constexpr int DITHER_FLAG = 0;

            static constexpr int SAMPLE_SIZE = 4;
            static constexpr float SAMPLE_SILENCE = 0.0f;
    };
}


#endif //MY_SKYPE_AUDIOWRAPPER_HPP

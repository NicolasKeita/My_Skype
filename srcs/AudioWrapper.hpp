//
// Created by spynight on 12/26/19.
//

#ifndef MY_SKYPE_AUDIOWRAPPER_HPP
#define MY_SKYPE_AUDIOWRAPPER_HPP

#include <boost/any.hpp>
#include "portaudio.h"

using SAMPLE = float;
#define SAMPLE_SILENCE (0.0f)

namespace babel {
    class NetworkHandler;
    class AudioWrapper {
        public:
            explicit AudioWrapper(NetworkHandler &network);

            void playRecord(std::vector<float> record);
            std::vector<float> getRecord();
            void restartStream();
            void startStream();
            void closeStream();
            void stopStream();
            void stopRecording();
            void startRecording();
            bool isRecording();
            bool isStreaming();

        private:
            PaStream            *_streamMyVoice;
            PaStream            *_streamTheirVoice;
            PaError             _err;
            char                *_sampleBlock;
            int                 _i;
            SAMPLE              max;
            SAMPLE              val;
            double              average;
            NetworkHandler      &network;
            bool                _streaming;
            bool                _recording;
            int                 _bufferSize; // AKA FramesPerBuffer
            uint32_t            _sampleRate;
    };
}


#endif //MY_SKYPE_AUDIOWRAPPER_HPP

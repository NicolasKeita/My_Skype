//
// Created by spynight on 12/26/19.
//

#ifndef MY_SKYPE_AUDIOWRAPPER_HPP
#define MY_SKYPE_AUDIOWRAPPER_HPP

#include <portaudio.h>
#include "IAudioWrapper.hpp"
#include "NetworkHandler.hpp"

using SAMPLE = float;
#define SAMPLE_SILENCE (0.0f)

namespace babel {
    class NetworkHandler;
    class AudioWrapper : public IAudioWrapper {
        public:
            explicit AudioWrapper(NetworkHandler &network);

            void playRecord(std::vector<SAMPLE> record) override;
            std::vector<SAMPLE> getRecord() override;
            void restartStream() override;
            void startStream() override;
            void closeStream() override;
            void stopStream() override;
            void stopRecording() override;
            void startRecording() override;
            bool isRecording() override;
            bool isStreaming() override;

        private:
            PaStream            *_stream;
            NetworkHandler      &network;
            bool                _streaming;
            bool                _recording;
            int                 _bufferSize; // AKA FramesPerBuffer
            int                 _sampleRate;
    };
}


#endif //MY_SKYPE_AUDIOWRAPPER_HPP

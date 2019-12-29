//
// Created by spynight on 12/29/19.
//

#ifndef MY_SKYPE_IAUDIOWRAPPER_HPP
#define MY_SKYPE_IAUDIOWRAPPER_HPP

namespace babel {
    class IAudioWrapper {
        public:
            virtual void playRecord(std::vector<float> record) = 0;
            virtual std::vector<float> getRecord() = 0;
            virtual void restartStream() = 0;
            virtual void startStream() = 0;
            virtual void closeStream() = 0;
            virtual void stopStream() = 0;
            virtual void stopRecording() = 0;
            virtual void startRecording() = 0;
            virtual bool isRecording() = 0;
            virtual bool isStreaming() = 0;
    };
}

#endif //MY_SKYPE_IAUDIOWRAPPER_HPP

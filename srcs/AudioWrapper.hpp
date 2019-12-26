//
// Created by spynight on 12/26/19.
//

#ifndef MY_SKYPE_AUDIOWRAPPER_HPP
#define MY_SKYPE_AUDIOWRAPPER_HPP

#include <boost/any.hpp>
#include "portaudio.h"

#define PA_SAMPLE_TYPE  paFloat32
#define PRINTF_S_FORMAT "%.8f"

namespace babel {
    class AudioWrapper {
        public:
            AudioWrapper() = default;

            boost::any recordInputVoice();
            void listenSound(const boost::any &reply);

            static constexpr int SAMPLE_RATE = 44100;
            static constexpr int FRAMES_PER_BUFFER = 512;
            static constexpr int NUM_SECONDS = 10;
            static constexpr int DITHER_FLAG = 0;

            static constexpr int SAMPLE_SIZE = 4;
            static constexpr float SAMPLE_SILENCE = 0.0f;
    };
}


#endif //MY_SKYPE_AUDIOWRAPPER_HPP

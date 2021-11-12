#pragma once
#include <cstdint>

using namespace std;


class AudioUtils
{
private:
    /* data */
    uint8_t SetSysClock_PLL_HSE_200MHz();
public:
    AudioUtils();
    ~AudioUtils();
    void initAudio(uint16_t* audioBufferIn, uint32_t numOfElements);
    void initSDRAM(void);
    void startAudioRecording(uint16_t* audioBufferIn, uint32_t numOfElements);
    void stopAudioRecording(void);
    void setAudioBufferEmpty(void);
    void setAudioBufferFull(void);
    bool isAudioAvailable(void);
    bool isAudioUnavailable(void);
    void convertStereoToMono(int16_t* bufferIn, int16_t* bufferOut, uint32_t numOfBytes);

    uint32_t audio_rec_buffer_state;
};



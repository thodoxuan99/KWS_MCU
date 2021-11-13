#pragma once
#include <cstring>
#include <vector>
#include <string>
#include <memory>
#include "KWS.h"
#include "AudioUtils.h"


using namespace std;

class KWSInstance : public KWS
{
private:
    static KWSInstance *_instance;
    vector<string>output_class_;
    int detect_threshold;
    KWSInstance(int recordingWindow, int slidingWindowLen, std::vector<std::string>& outputClass, int detectionThreshold);
    ~KWSInstance();
public:
    static KWSInstance* getInstance();
    void StartKWS(void);
    void RunKWS(void);
    void StartRecording(void);
    void StopRecording(void);
    void SetAudioBufferEmpty(void);
    bool IsAudioBufferAvailable(void);
    void ConvertStereoBufToMonoBuffer(void);

    vector<int16_t> audio_in_buffer;
    vector<int16_t> audio_accum_buffer;
    std::unique_ptr<AudioUtils> audio_utils;
};


// extern KWSInstance* KWSInstancePtr;
#pragma once
#include <arm_math.h>
#include <vector>

using namespace std;

class KWS
{
private:
    /* data */
public:
    KWS(int recordingWindow, int slidingWindowLen);
    ~KWS();
    void ExtractFeatures(void);
    void Classify(void);
    void AveragePredictions(void);
    int GetTopClass(const vector<float>& predictions);

    vector<int16_t> mono_audio_buffer;
    vector<float> average_output;

};

KWS::KWS(int recordingWindow, int slidingWindowLen)
{
}

KWS::~KWS()
{
}

#include "KWSInstance.h"
#include "DefineMacros.h"
#include "stm32746g_discovery.h"
#include "stm32746g_discovery_audio.h"

using namespace std;

KWSInstance *KWSInstance::_instance = NULL;

KWSInstance *KWSInstance::getInstance(){
    if(_instance == NULL){
        _instance = new KWSInstance(recording_windows, window_len, output_class, detection_threshold);
    }
    return _instance;
}

KWSInstance::KWSInstance(int recordingWindow, int slidingWindowLen, std::vector<std::string>& outputClass, int detectionThreshold)
        : KWS(recordingWindow, slidingWindowLen)     
{
    output_class_ = outputClass;
    detect_threshold = detectionThreshold;
    audio_in_buffer = vector<int16_t>(AUDIO_BLOCK_SIZE << 1);
    audio_accum_buffer = vector<int16_t>(AUDIO_ACCUM_BUFFER_SIZE << 1);

    this->audio_utils = unique_ptr<AudioUtils>(new AudioUtils());
}

void KWSInstance::StartKWS(void){
    memset(audio_in_buffer.data(), 0, audio_in_buffer.size()*sizeof(int16_t));
    memset(audio_accum_buffer.data(), 0, audio_accum_buffer.size()*sizeof(int16_t));
    memset(mono_audio_buffer.data(), 0, mono_audio_buffer.size()*sizeof(int16_t));
    this->audio_utils->initAudio(audio_in_buffer.data(), audio_in_buffer.size());

    printf("KWS instance init done.\n");
}

void KWSInstance::RunKWS(void){
    printf("EXTRACTING FEATURES...\n");
    this->ExtractFeatures();
    printf("CLASSIFYING...\n");
    this->Classify();
    printf("AVERAGING PREDICTIONS...\n");
    this->AveragePredictions();
    int maxConfidenceIdx = this->GetTopClass(this->average_output);

    if((int)(getInstance()->average_output[maxConfidenceIdx] * 100) >= this->detect_threshold){
        printf("***CLASSIFIED WITH %d% CONFIDENCE***\n", (int)(getInstance()->average_output[maxConfidenceIdx] * 100));
    }
    else{
        printf("CLASSIFIED WITH LOW CONFIDENCE\n");
    }
}

void KWSInstance::StartRecording(void){
    return _instance->audio_utils->startAudioRecording((uint16_t *)audio_in_buffer.data(), audio_in_buffer.size());
}

void KWSInstance::StopRecording(void){
    return _instance->audio_utils->stopAudioRecording();
}

bool KWSInstance::IsAudioBufferAvailable(void){
    return _instance->audio_utils->isAudioAvailable();
}

void KWSInstance::SetAudioBufferEmpty(void){
    getInstance()->audio_utils->setAudioBufferEmpty();
}

void KWSInstance::ConvertStereoBufToMonoBuffer(void){
    return this->audio_utils->convertStereoToMono(this->audio_accum_buffer.data(),
            this->mono_audio_buffer.data(),
            this->audio_accum_buffer.size() * sizeof(int16_t));
}

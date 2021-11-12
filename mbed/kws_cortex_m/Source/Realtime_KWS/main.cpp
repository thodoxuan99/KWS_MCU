#include "mbed.h"
#include "KWSInstance.h"
#include "DefineMacros.h"

// main() runs in its own thread in the OS
int main()
{
    printf("Starting KWS...\n");
    KWSInstance::getInstance()->StartKWS();
    KWSInstance::getInstance()->SetAudioBufferEmpty();

    KWSInstance::getInstance()->StartRecording();
    while (true) {
        /* A dummy loop to wait for the interrupts. */
        __WFI();
        if(KWSInstance::getInstance()->IsAudioBufferAvailable()){
            KWSInstance::getInstance()->StopRecording();
            KWSInstance::getInstance()->SetAudioBufferEmpty();
            KWSInstance::getInstance()->ConvertStereoBufToMonoBuffer();
            KWSInstance::getInstance()->StartRecording();
            KWSInstance::getInstance()->RunKWS();
        }
    }
}


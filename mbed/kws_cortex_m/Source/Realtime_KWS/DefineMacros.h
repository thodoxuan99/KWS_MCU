#include "stm32746g_discovery_sdram.h"
#include <cstring>
#include <vector>

#ifndef __DEFINE_MACROS__
#define __DEFINE_MACROS__
#define AUDIO_BUFFER_IN             (SDRAM_DEVICE_ADDR)
#define AUDIO_BLOCK_SIZE            (512U)
#define NUM_OF_AUDIO_BLOCKS         (((16000U) * 2) / AUDIO_BLOCK_SIZE)
#define AUDIO_ACCUM_BUFFER          (AUDIO_BUFFER_IN + AUDIO_BLOCK_SIZE * 2)
#define AUDIO_ACCUM_BUFFER_SIZE     (AUDIO_BLOCK_SIZE * NUM_OF_AUDIO_BLOCKS)

int recording_windows = 49;
int window_len = 1;
int detection_threshold = 50;

std::vector<std::string> output_class = {
    "BACH KHOA OI",
    "BACH",
    "KHOA",
    "OI"
};
#endif


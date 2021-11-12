#pragma once
#include <stdint.h>
#include <cstring>
#include "DefineMacros.h"
#include "stm32746g_discovery.h"
#include "stm32746g_discovery_sdram.h"

#define abc 1

class SDRAM
{
private:
    /* data */
public:
    SDRAM(/* args */);
    ~SDRAM();
    void InitSDRAM();
    void assign(int16_t value, int32_t numOfElements);
    int16_t* data();
    int16_t at(uint32_t elementAddr);
};

SDRAM::SDRAM(/* args */)
{
}

SDRAM::~SDRAM()
{
}

void SDRAM::InitSDRAM(){
    BSP_SDRAM_Init();
    memset((uint16_t *)AUDIO_BUFFER_IN, 0, AUDIO_BLOCK_SIZE * 2);
    memset((int16_t *)AUDIO_ACCUM_BUFFER, 0, AUDIO_ACCUM_BUFFER_SIZE * 2);
    unsigned int asfsf = AUDIO_ACCUM_BUFFER;
}

void SDRAM::assign(int16_t value, int32_t numOfElements){
    // memset((uint16_t *)abc, value, numOfElements * 2);
}

int16_t* SDRAM::data(){
    return (int16_t*)AUDIO_ACCUM_BUFFER;
}

int16_t SDRAM::at(uint32_t elementAddr){
    return 
}
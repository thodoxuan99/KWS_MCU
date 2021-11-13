#include <cstring>
#include "stm32746g_discovery.h"
#include "stm32746g_discovery_audio.h"
#include "stm32746g_discovery_sdram.h"
#include "mbed_assert.h"
#include "AudioUtils.h"
#include "KWSInstance.h"
#include "DefineMacros.h"


typedef enum {
    BUFFER_OFFSET_NONE = 0,
    BUFFER_OFFSET_FULL = 1,
} BUFFER_StateTypeDef;

extern KWSInstance* KWSInstancePtr;

void BSP_AUDIO_IN_TransferComplete_CallBack(void)
{

}

void BSP_AUDIO_IN_HalfTransfer_CallBack(void)
{
}

/**
 * @brief  Audio IN Error callback function
 */
void BSP_AUDIO_IN_Error_CallBack(void)
{
    MBED_ASSERT(0);
}

AudioUtils::AudioUtils()
{
    this->SetSysClock_PLL_HSE_200MHz();
    this->initSDRAM();
}

AudioUtils::~AudioUtils()
{
}

void AudioUtils::initSDRAM(void){
    BSP_SDRAM_Init();
    // memset((uint16_t*)AUDIO_BUFFER_IN, 0, AUDIO_BLOCK_SIZE * sizeof(uint16_t));
    printf("\nSDRAM init done\n");
}

void AudioUtils::initAudio(uint16_t* audioBufferIn, uint32_t numOfElements){
    if (BSP_AUDIO_IN_InitEx(INPUT_DEVICE_DIGITAL_MICROPHONE_2,DEFAULT_AUDIO_IN_FREQ, DEFAULT_AUDIO_IN_BIT_RESOLUTION, DEFAULT_AUDIO_IN_CHANNEL_NBR) != AUDIO_OK)
    {
        printf("BSP_AUDIO_IN_Init error\r\n");
    }

    /* Start Recording */
    if (BSP_AUDIO_IN_Record((uint16_t *)audioBufferIn, numOfElements) != AUDIO_OK)
    {
        printf("BSP_AUDIO_IN_Record init error\r\n");
    }

    /* Stop Recording until memory allocation etc for model is complete*/
    if (BSP_AUDIO_IN_Stop(CODEC_PDWN_SW) != AUDIO_OK)
    {
        printf("BSP_AUDIO_IN_Stop error\r\n");
    }

    this->audio_rec_buffer_state = BUFFER_OFFSET_NONE;

    printf("AUDIO recording configured from digital microphones (U20 & U21 components on board) \r\n");
}

void AudioUtils::startAudioRecording(uint16_t* audioBufferIn, uint32_t numOfElements){
    if (BSP_AUDIO_IN_Record(audioBufferIn, numOfElements) != AUDIO_OK)
    {
        printf("BSP_AUDIO_IN_Record error\r\n");
    }
}

void AudioUtils::stopAudioRecording(void){
    if (BSP_AUDIO_IN_Stop(CODEC_PDWN_SW) != AUDIO_OK)
    {
        printf("BSP_AUDIO_Stop error\r\n");
    }
}

bool AudioUtils::isAudioAvailable(void){
    return this->audio_rec_buffer_state == BUFFER_OFFSET_FULL;
}

bool AudioUtils::isAudioUnavailable(void){
    return this->audio_rec_buffer_state == BUFFER_OFFSET_NONE;
}

void AudioUtils::setAudioBufferEmpty(void){
    this->audio_rec_buffer_state = BUFFER_OFFSET_NONE;
}

void AudioUtils::setAudioBufferFull(void){
    this->audio_rec_buffer_state = BUFFER_OFFSET_FULL;
}

uint8_t AudioUtils::SetSysClock_PLL_HSE_200MHz()
{
    RCC_ClkInitTypeDef RCC_ClkInitStruct;
    RCC_OscInitTypeDef RCC_OscInitStruct;

    // Enable power clock
    __PWR_CLK_ENABLE();

    // Enable HSE oscillator and activate PLL with HSE as source
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON; /* External xtal on OSC_IN/OSC_OUT */

    // Warning: this configuration is for a 25 MHz xtal clock only
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 25;            // VCO input clock = 1 MHz (25 MHz / 25)
    RCC_OscInitStruct.PLL.PLLN = 400;           // VCO output clock = 400 MHz (1 MHz * 400)
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2; // PLLCLK = 200 MHz (400 MHz / 2)
    RCC_OscInitStruct.PLL.PLLQ = 8;             // USB clock = 50 MHz (400 MHz / 8)

    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        return 0; // FAIL
    }

    // Activate the OverDrive to reach the 216 MHz Frequency
    if (HAL_PWREx_EnableOverDrive() != HAL_OK)
    {
        return 0; // FAIL
    }

    // Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
    // clocks dividers
    RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK |
                                   RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK; // 200 MHz
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;        // 200 MHz
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;         //  50 MHz
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;         // 100 MHz

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
    {
        return 0; // FAIL
    }
    HAL_RCC_MCOConfig(RCC_MCO1, RCC_MCO1SOURCE_HSE, RCC_MCODIV_4);
    return 1; // OK
}
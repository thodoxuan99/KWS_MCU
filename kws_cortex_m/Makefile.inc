# ifneq ($(filter Simple_KWS_Test,$(ALL_TAGS)),)
#     APPLICATION = Simple_KWS_Test
# else ifneq ($(filter Realtime_KWS_Test,$(ALL_TAGS)),)
#     APPLICATION = Realtime_KWS_Test
# else
#     $(error Error parsing the application to use. Applications available are: [Simple_KWS_Test, Realtime_KWS_Test])
# endif
# THIRD_PARTY_DOWNLOADS += \
#     $(eval $(call add_third_party_download,$(CMSIS_URL),$(CMSIS_MD5),cmsis,))

APPLICATION = Realtime_KWS

THIRD_PARTY_DOWNLOADS += \
    $(eval $(call add_third_party_download,$(CMSIS_URL),$(CMSIS_MD5),cmsis,))

CMSIS_PATH = $(MAKEFILE_DIR)/downloads/cmsis

CMSIS_DSP_SRCS += \
    $(CMSIS_PATH)/CMSIS/DSP/Source/TransformFunctions/arm_cfft_f32.c \
    $(CMSIS_PATH)/CMSIS/DSP/Source/TransformFunctions/arm_cfft_init_f32.c \
    $(CMSIS_PATH)/CMSIS/DSP/Source/TransformFunctions/arm_cfft_radix2_f32.c \
    $(CMSIS_PATH)/CMSIS/DSP/Source/TransformFunctions/arm_cfft_radix2_init_f32.c \
    $(CMSIS_PATH)/CMSIS/DSP/Source/TransformFunctions/arm_cfft_radix4_f32.c \
    $(CMSIS_PATH)/CMSIS/DSP/Source/TransformFunctions/arm_cfft_radix4_init_f32.c \
    $(CMSIS_PATH)/CMSIS/DSP/Source/TransformFunctions/arm_cfft_radix8_f32.c \
    $(CMSIS_PATH)/CMSIS/DSP/Source/TransformFunctions/arm_dct4_f32.c \
    $(CMSIS_PATH)/CMSIS/DSP/Source/TransformFunctions/arm_dct4_init_f32.c \
    $(CMSIS_PATH)/CMSIS/DSP/Source/TransformFunctions/arm_rfft_f32.c \
    $(CMSIS_PATH)/CMSIS/DSP/Source/TransformFunctions/arm_rfft_fast_f32.c \
    $(CMSIS_PATH)/CMSIS/DSP/Source/TransformFunctions/arm_rfft_fast_init_f32.c \
    $(CMSIS_PATH)/CMSIS/DSP/Source/TransformFunctions/arm_rfft_init_f32.c \
    $(CMSIS_PATH)/CMSIS/DSP/Source/TransformFunctions/arm_bitreversal2.c \
    $(CMSIS_PATH)/CMSIS/DSP/Source/FastMathFunctions/arm_cos_f32.c \
    $(CMSIS_PATH)/CMSIS/DSP/Source/FastMathFunctions/arm_cos_q15.c \
    $(CMSIS_PATH)/CMSIS/DSP/Source/FastMathFunctions/arm_sin_f32.c \
    $(CMSIS_PATH)/CMSIS/DSP/Source/FastMathFunctions/arm_sin_q15.c \
    $(CMSIS_PATH)/CMSIS/DSP/Source/FastMathFunctions/arm_sqrt_q15.c \
    $(CMSIS_PATH)/CMSIS/DSP/Source/FastMathFunctions/arm_vexp_f32.c \
    $(CMSIS_PATH)/CMSIS/DSP/Source/FastMathFunctions/arm_vlog_f32.c \
    $(CMSIS_PATH)/CMSIS/DSP/Source/CommonTables/arm_const_structs.c \
    $(CMSIS_PATH)/CMSIS/DSP/Source/CommonTables/arm_common_tables.c

CMSIS_DSP_HDRS += \
    $(CMSIS_PATH)/CMSIS/DSP/Include/dsp/transform_functions.h \
    $(CMSIS_PATH)/CMSIS/DSP/Include/dsp/none.h \
    $(CMSIS_PATH)/CMSIS/DSP/Include/dsp/utils.h \
    $(CMSIS_PATH)/CMSIS/DSP/Include/dsp/basic_math_functions.h \
    $(CMSIS_PATH)/CMSIS/DSP/Include/dsp/complex_math_functions.h \
    $(CMSIS_PATH)/CMSIS/DSP/Include/dsp/fast_math_functions.h \
    $(CMSIS_PATH)/CMSIS/DSP/Include/arm_math.h \
    $(CMSIS_PATH)/CMSIS/DSP/Include/arm_math_types.h \
    $(CMSIS_PATH)/CMSIS/DSP/Include/arm_math_memory.h \
    $(CMSIS_PATH)/CMSIS/DSP/Include/arm_common_tables.h \
    $(CMSIS_PATH)/CMSIS/DSP/Include/arm_const_structs.h \
    $(CMSIS_PATH)/CMSIS/DSP/PrivateInclude/arm_sorting.h 


INCLUDES += -I$(CMSIS_PATH) \
            -I$(CMSIS_PATH)/CMSIS/DSP/Include \
            -I$(CMSIS_PATH)/CMSIS/DSP/Include/dsp \
            -I$(CMSIS_PATH)/CMSIS/DSP/PrivateInclude

GENERATED_PROJECT_INCLUDES += $(INCLUDES)

# ifneq ($(filter DNN,$(ALL_TAGS)),)
# #Include DNN files if within the TAGS
#     MODEL = DNN
# else ifneq ($(filter DS_CNN,$(ALL_TAGS)),)
# #Include DS_CNN files if within the TAGS
#     MODEL = DS_CNN
# else
#    $(error Error parsing the model to use. Models available are: [DNN, DS_CNN])
# endif

MODEL = DS_CNN

#Include common files
KWS_CORTEX_M_HDRS := \
    $(wildcard tensorflow/lite/micro/examples/kws_cortex_m/Source/AudioUtils/*.h) \
    $(call recursive_find, tensorflow/lite/micro/examples/kws_cortex_m/Source/AudioUtils,*.h) \
    $(wildcard tensorflow/lite/micro/examples/kws_cortex_m/Source/KWS/*.h) \
    $(call recursive_find, tensorflow/lite/micro/examples/kws_cortex_m/Source/MFCC,*.h) \
    $(wildcard tensorflow/lite/micro/examples/kws_cortex_m/Source/NeuralNetwork/*.h) \
    $(call recursive_find, tensorflow/lite/micro/examples/kws_cortex_m/Source/KWS/KWS_$(MODEL),*.h) \
    $(call recursive_find, tensorflow/lite/micro/examples/kws_cortex_m/Source/NeuralNetwork/$(MODEL),*.h) \
    $(call recursive_find, tensorflow/lite/micro/examples/kws_cortex_m/Source/$(APPLICATION),*.h) \
    $(CMSIS_DSP_HDRS)

KWS_CORTEX_M_SRCS := \
    $(wildcard tensorflow/lite/micro/examples/kws_cortex_m/Source/AudioUtils/*.cpp) \
    $(call recursive_find, tensorflow/lite/micro/examples/kws_cortex_m/Source/AudioUtils,*.cpp) \
    $(wildcard tensorflow/lite/micro/examples/kws_cortex_m/Source/KWS/*.cpp) \
    $(call recursive_find, tensorflow/lite/micro/examples/kws_cortex_m/Source/MFCC,*.cpp) \
    $(wildcard tensorflow/lite/micro/examples/kws_cortex_m/Source/NeuralNetwork/*.cpp) \
    $(call recursive_find, tensorflow/lite/micro/examples/kws_cortex_m/Source/Generated/$(MODEL),*.cpp) \
    $(call recursive_find, tensorflow/lite/micro/examples/kws_cortex_m/Source/KWS/KWS_$(MODEL),*.cpp) \
    $(call recursive_find, tensorflow/lite/micro/examples/kws_cortex_m/Source/NeuralNetwork/$(MODEL),*.cpp) \
    $(call recursive_find, tensorflow/lite/micro/examples/kws_cortex_m/Source/$(APPLICATION),*.cpp) \
    $(CMSIS_DSP_SRCS)

$(eval $(call generate_microlite_projects,kws_cortex_m,$(call specialize,$(KWS_CORTEX_M_SRCS)),$(KWS_CORTEX_M_HDRS)))

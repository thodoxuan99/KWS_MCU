# BUILD
## Dataset
http://download.tensorflow.org/data/speech_commands_v0.02.tar.gz

- Keep only 18 words set
## Training
- Wanted words : "Go" and "Sheila"
```
python3 train.py --model_architecture ds_cnn --model_size_info 5 64 10 4 2 2 64 3 3 1 1 64 3 3 1 1 64 3 3 1 1 64 3 3 1 1 --dct_coefficient_count 10 --window_size_ms 40 --window_stride_ms 20 --learning_rate 0.0005,0.0001,0.00002 --how_many_training_steps 10000,10000,10000 --summaries_dir work/DS_CNN/DS_CNN1/retrain_logs --train_dir work/DS_CNN/DS_CNN1/training --wanted_words "go,sheila"
```

## Convert to Tflite
```
python3 convert.py --model_architecture ds_cnn --model_size_info 5 64 10 4 2 2 64 3 3 1 1 64 3 3 1 1 64 3 3 1 1 64 3 3 1 1 --dct_coefficient_count 10 --window_size_ms 40 --window_stride_ms 20 --learning_rate 0.0005,0.0001,0.00002 --how_many_training_steps 10000,10000,10000 --summaries_dir work/DS_CNN/DS_CNN1/retrain_logs --train_dir work/DS_CNN/DS_CNN1/training --wanted_words "go,sheila" --checkpoint work/DS_CNN/DS_CNN1/training/best/ds_cnn_0.967_ckpt
```
## Tflite to C array 
```
python3 tflite_to_tflu.py --tflite_path ../Training/ds_cnn_quantized.tflite --output_path ds_cnn_s_tflu.cc
```

## Custom Wanted-Words in mbed_source code: "Go" and "Sheila"
In file [main.cc](mbed/tensorflow/lite/micro/examples/kws_cortex_m/Source/Applications/Realtime_KWS_Test/main.cc)

```c
    std::vector<std::string> outputClass = {
    "Silence",
    "Unknown",
    "go",
    "sheila"
    };
```

## Build mbed.bin image for Board STM32F746NG
```
cd mbed
#rm -rf /tensorflow/lite/micro/examples/kws_cortex_m
#cp -r ../kws_cortex_m/ tensorflow/lite/micro/examples/
mbed compile -m DISCO_F746NG -t GCC_ARM --source .  --source ../CMSIS_5/CMSIS/DSP/Include   --source ../CMSIS_5/CMSIS/Core/Include --source ../CMSIS_5/CMSIS/DSP/PrivateInclude/
```


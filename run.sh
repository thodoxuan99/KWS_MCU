git clone https://github.com/ARM-software/ML-examples.git
git clone https://github.com/thodoxuan99/KWS_MCU.git 

echo "Clone Repo"
cd ML-examples/tflu-kws-cortex-m
git clone https://github.com/tensorflow/tensorflow.git
cd tensorflow
git checkout 72c19e8880
cd ../../../

echo "Training"
cd KWS_MCU/Training
python3 train.py --model_architecture ds_cnn --model_size_info 5 64 10 4 2 2 64 3 3 1 1 64 3 3 1 1 64 3 3 1 1 64 3 3 1 1 --dct_coefficient_count 10 --window_size_ms 40 --window_stride_ms 20 --learning_rate 0.0005,0.0001,0.00002 --how_many_training_steps 10000,10000,10000 --summaries_dir work/DS_CNN/DS_CNN1/retrain_logs --train_dir work/DS_CNN/DS_CNN1/training --wanted_words "go,up"


python3 convert.py --model_architecture ds_cnn --model_size_info 5 64 10 4 2 2 64 3 3 1 1 64 3 3 1 1 64 3 3 1 1 64 3 3 1 1 --dct_coefficient_count 10 --window_size_ms 40 --window_stride_ms 20 --learning_rate 0.0005,0.0001,0.00002 --how_many_training_steps 10000,10000,10000 --summaries_dir work/DS_CNN/DS_CNN1/retrain_logs --train_dir work/DS_CNN/DS_CNN1/training --wanted_words "go,up" --checkpoint work/DS_CNN/DS_CNN1/training/best/ds_cnn_0.967_ckpt

cd ../kws_cortex_m
python3 tflite_to_tflu.py --tflite_path ../Training/ds_cnn_quantized.tflite --output_path ../mbed/tensorflow/lite/micro/examples/Generated/DS_CNN/ds_cnn_s_tflu.cc


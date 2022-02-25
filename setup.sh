git clone https://github.com/ARM-software/ML-examples.git
git clone https://github.com/thodoxuan99/KWS_MCU.git 

echo "Clone Repo"
cd ML-examples/tflu-kws-cortex-m
git clone https://github.com/tensorflow/tensorflow.git
cd tensorflow
git checkout 72c19e8880
cd ../../../
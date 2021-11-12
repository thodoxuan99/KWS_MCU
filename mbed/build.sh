cd ~/Mbed\ Programs/Thesis_KWS/ &&
rm -r tensorflow/tensorflow/lite/micro/examples/kws_cortex_m/ &&
cp -r ./kws_cortex_m tensorflow/tensorflow/lite/micro/examples/ &&
cd tensorflow &&
make -f tensorflow/lite/micro/tools/make/Makefile generate_kws_cortex_m_mbed_project &&
cd tensorflow/lite/micro/tools/make/gen/linux_x86_64/prj/kws_cortex_m/mbed/ &&
mbed config root . &&
mbed deploy &&
mbed compile -m DISCO_F746NG -t GCC_ARM --source . --source ../CMSIS_5/CMSIS/DSP/Include   --source ../CMSIS_5/CMSIS/Core/Include --source ../CMSIS_5/CMSIS/DSP/PrivateInclude/


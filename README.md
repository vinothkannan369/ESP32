# ESP32

ESP32 commands

To Erase flash
esptool.py --chip esp32 erase_flash 

To Build         
idf.py build

To go to menuconfig
idf.py menuconfig

Monitoring
idf.py -p COM3 flash monitor

To Check partition
idf.py partition-table

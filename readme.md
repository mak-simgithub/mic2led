on raspi:
sudo raspi-config

enable vnc and i2c

sudo nano /boot/firmware/config.txt

add

dtoverlay=hifiberry-adc

sudo reboot

mit arecord -l checken ob erkannt und welchen index die soundcard hat 0,1?

amixer scontrols -c 0
amixer sset "ADC Left Input" "{VIN1P, VIN1M}[DIFF]" -c 0
amixer sset "ADC Right Input" "{VIN2P, VIN2M}[DIFF]" -c 0
amixer sset ADC 40db -c 0


install puredata

sudo apt-get install puredata



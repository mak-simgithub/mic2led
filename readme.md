on raspi: (mic2led1 and mic2led2, user pi, pw standard luca pi pw)
sudo raspi-config

enable vnc

sudo nano /boot/firmware/config.txt

add

dtoverlay=hifiberry-adc

sudo reboot

mit arecord -l checken ob erkannt und welchen index die soundcard hat 0,1?

amixer scontrols -c 1
amixer sset "ADC Left Input" "{VIN1P, VIN1M}[DIFF]" -c 1
amixer sset "ADC Right Input" "{VIN2P, VIN2M}[DIFF]" -c 1
amixer sset ADC 40db -c 1
sudo alsactl store


curl -fsSL https://tailscale.com/install.sh | sh

sudo tailscale up --auth-key=tskey-auth-kWtA6xaimv11CNTRL-TS3DmZV2bhaUCMSZuzSngaJyLp8EFu5qF

sudo apt install puredata

mkdir repos

cd repos

git clone https://github.com/mak-simgithub/mic2led.git

sudo apt install python3-rpi.gpio

sudo mv mic2led.service /etc/systemd/system/mic2led.service

sudo systemctl daemon-reload
sudo systemctl enable mic2led.service
sudo systemctl start mic2led.service



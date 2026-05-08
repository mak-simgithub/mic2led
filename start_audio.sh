#!/bin/bash

# Wait for ALSA
until amixer -c 1 info >/dev/null 2>&1; do
    sleep 0.2
done

# Force ADC init
amixer -c 1 sset ADC 10db
sleep 0.2
amixer -c 1 sset ADC 40db
sleep 0.2

# Start Python in background
/usr/bin/python3 /home/pi/repos/mic2led/udp2gpio.py &

# Start Pd in foreground (main process)
exec /usr/bin/pd -nogui /home/pi/repos/mic2led/basic.pd

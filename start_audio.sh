#!/bin/bash

# Ensure ALSA is ready
until amixer -c 1 info >/dev/null 2>&1; do
    sleep 0.2
done

# Set gain low → high to force reinit
amixer -c 1 sset ADC 10db
sleep 0.2
amixer -c 1 sset ADC 40db
sleep 0.2

# Start Pd
/usr/bin/pd -nogui /home/pi/repos/mic2led/basic.pd

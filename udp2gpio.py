import socket
import RPi.GPIO as GPIO

UDP_IP = "127.0.0.1"
UDP_PORT = 5000

PIN_A = 26   # channel 1
PIN_B = 13   # channel 2

GPIO.setmode(GPIO.BCM)
GPIO.setup(PIN_A, GPIO.OUT)
GPIO.setup(PIN_B, GPIO.OUT)

# 500 Hz PWM (you can adjust)
pwm_a = GPIO.PWM(PIN_A, 500)
pwm_b = GPIO.PWM(PIN_B, 500)

pwm_a.start(0)
pwm_b.start(0)

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((UDP_IP, UDP_PORT))

print("RPi.GPIO PWM server running...")

def set_pwm(channel, value):
    # clamp 0–1024
    value = max(0, min(1024, value))
    duty = (value / 1024) * 100  # convert to 0–100%

    if channel == 1:
        pwm_a.ChangeDutyCycle(duty)
    elif channel == 2:
        pwm_b.ChangeDutyCycle(duty)

while True:
    data, addr = sock.recvfrom(1024)
    try:
        msg = data.decode().strip().replace(";", "")
        parts = msg.split()

        if len(parts) != 2:
            continue

        channel = int(parts[0])
        value = int(parts[1])

        set_pwm(channel, value)

    except Exception as e:
        print("Error:", e)
        pass

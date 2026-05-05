import socket
import pigpio

UDP_IP = "127.0.0.1"
UDP_PORT = 5000

pi = pigpio.pi()
PIN_A = 26   # for messages starting with "1"
PIN_B = 13   # for messages starting with "2"

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((UDP_IP, UDP_PORT))

print("I2C bridge running...")

while True:
    data, addr = sock.recvfrom(1024)

    try:
        msg = data.decode().strip()
        parts = msg.split()

        if len(parts) != 2:
            continue

        channel = int(parts[0])
        value   = int(parts[1])

        # clamp to 0–1024 for pigpio PWM
        value = max(0, min(1024, value))

        if channel == 1:
            print(f"CH1 → {value}")
            pi.set_PWM_dutycycle(PIN_A, value)

        elif channel == 2:
            print(f"CH2 → {value}")
            pi.set_PWM_dutycycle(PIN_B, value)

    except Exception as e:
        print("Error:", e)
        pass

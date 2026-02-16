import socket
import smbus

UDP_IP = "127.0.0.1"
UDP_PORT = 5000

I2C_ADDR = 0x08
bus = smbus.SMBus(1)

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((UDP_IP, UDP_PORT))

print("I2C bridge running...")

while True:
    data, addr = sock.recvfrom(1024)
    parts = data.decode().strip().split()

    if len(parts) != 2:
        print("Expected: index value")
        continue

    index = int(parts[0].strip(" ;\n\r"))
    value = int(parts[1].strip(" ;\n\r"))

    bus.write_i2c_block_data(I2C_ADDR, 0, [index, value])

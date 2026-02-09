import pigpio
import time

# GPIO pins
ZC_PIN = 17      # Zero-cross input
DIM_PIN = 27     # Dimmer trigger output

# Initialize pigpio
pi = pigpio.pi()
if not pi.connected:
    raise Exception("Could not connect to pigpio daemon")

pi.set_mode(ZC_PIN, pigpio.INPUT)
pi.set_mode(DIM_PIN, pigpio.OUTPUT)
pi.write(DIM_PIN, 0)

# AC frequency (adjust if you're on 60 Hz)
AC_FREQ = 50
HALF_CYCLE_US = int(1_000_000 / (2 * AC_FREQ))

# Global dimming value (0–100)
power = 50

def set_power(p):
    global power
    power = max(0, min(100, p))

def zero_cross_callback(gpio, level, tick):
    # Compute delay based on power level
    delay_us = int(HALF_CYCLE_US * (1 - power / 100.0))

    # Schedule the triac firing pulse
    pi.set_PWM_dutycycle(DIM_PIN, 0)  # ensure low
    pi.wave_clear()

    # Build a short pulse (100 µs)
    pulse = [
        pigpio.pulse(1 << DIM_PIN, 0, 100),   # HIGH 100 µs
        pigpio.pulse(0, 1 << DIM_PIN, 0)      # LOW
    ]

    pi.wave_add_generic(pulse)
    wid = pi.wave_create()

    if wid >= 0:
        pi.wave_send_once(wid)
        pi.wave_tx_at(delay_us)  # schedule after delay

# Attach callback
cb = pi.callback(ZC_PIN, pigpio.RISING_EDGE, zero_cross_callback)

print("Dimmer running. Use set_power(x) to change brightness.")
print("Press Ctrl+C to exit.")

try:
    while True:
        time.sleep(1)
except KeyboardInterrupt:
    pass

cb.cancel()
pi.stop()

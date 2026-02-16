#include <Wire.h>
#include <RBDdimmer.h>

#define ZC_PIN 2  // zero-cross pin (must be wired)

const int NUM_CHANNELS = 4;
int dimPins[NUM_CHANNELS] = {3, 4, 5, 6};

dimmerLamp dimmers[NUM_CHANNELS] = {
  dimmerLamp(3),
  dimmerLamp(4),
  dimmerLamp(5),
  dimmerLamp(6)
};

volatile uint8_t incoming[2];
volatile int idx = 0;

// Map 0–127 → 0 or 25–75
int mapDimmerValue(int v) {
  if (v <= 0) return 0;      // full off
  if (v > 127) v = 127;      // clamp
  return 25 + (v - 1) * 50 / 126;  // scale into 25–75
}

void receiveEvent(int howMany) {
  while (Wire.available()) {
    incoming[idx++] = Wire.read();

    if (idx == 2) {
      int ch = incoming[0];
      int val = incoming[1];
      idx = 0;

      if (ch < NUM_CHANNELS) {
        int mapped = mapDimmerValue(val);
        dimmers[ch].setPower(mapped);
      }
    }
  }
}

void setup() {
  Serial.begin(115200);

  for (int i = 0; i < NUM_CHANNELS; i++) {
    dimmers[i].begin(NORMAL_MODE, ON);
  }

  Wire.begin(0x12);  // I2C address
  Wire.onReceive(receiveEvent);
}

void loop() {
  // nothing needed
}

#include <RBDdimmer.h>
#include <math.h>

#define ZC_PIN 2
#define DIM_PIN 3

dimmerLamp dimmer(DIM_PIN);

const float freq = 0.1;          // 0.5 Hz
const float updateInterval = 10; // ms
unsigned long lastUpdate = 0;

// Your usable dimming range
const float minP = 25;
const float maxP = 75;

void setup() {
  Serial.begin(9600);
  dimmer.begin(NORMAL_MODE, ON);
}

void loop() {
  unsigned long now = millis();

  if (now - lastUpdate >= updateInterval) {
    lastUpdate = now;

    float t = now / 1000.0;

    // Normal sine 0–1
    float s = (sin(2 * PI * freq * t) + 1) * 0.5;

    // Map into usable range
    float power = minP + s * (maxP - minP);

    dimmer.setPower((int)power);
  }
}

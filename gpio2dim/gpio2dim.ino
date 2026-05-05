#include <RBDdimmer.h>

// 0–127 → 0-3.3v -> 0-1023/5*3.3=675 -> 65-85
#define max_adc 675
#define min_dimm 65
#define max_dimm 85

#define ZC_PIN 2  // zero-cross pin (must be wired)
const int NUM_CHANNELS = 4;

int dimPins[NUM_CHANNELS] = {3, 4, 5, 6};
int analogPins[NUM_CHANNELS] = {A0, A1, A2, A3};

bool debugMode = false;   // <<< SET TO true FOR SINE WAVE TEST

dimmerLamp dimmers[NUM_CHANNELS] = {
  dimmerLamp(3),
  dimmerLamp(4),
  dimmerLamp(5),
  dimmerLamp(6)
};


int mapDimmerValue(int v) {
  return map(v, 0, max_adc, min_dimm, max_dimm);
}

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < NUM_CHANNELS; i++) {
    dimmers[i].begin(NORMAL_MODE, ON);
  }

  Serial.println("Dimmer controller ready.");
}

void loop() {

  if (debugMode) {
    // 0.2 Hz = 5 second period
    float t = millis() / 1000.0;
    float phase = 2.0 * PI * 0.2 * t;  // 0.2 Hz

    for (int i = 0; i < NUM_CHANNELS; i++) {
      float s = (sin(phase + i * PI/2) + 1.0) * 0.5;  // 0–1
      int mapped = map(s*1000, 0, 1000, min_dimm, max_dimm);
      Serial.println(mapped);
      dimmers[i].setPower(mapped);
      delay(10);
    }
    return;
  }

  // Normal mode: read analog inputs
  for (int i = 0; i < NUM_CHANNELS; i++) {
    int raw = analogRead(analogPins[i]);
    Serial.print(i);
    Serial.print(": ");
    Serial.print(raw);
    Serial.print(" ");
    dimmers[i].setPower(mapDimmerValue(raw));
  }
  Serial.println();
}

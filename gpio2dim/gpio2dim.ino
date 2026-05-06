#include <RBDdimmer.h>

// 0–127 → 0-3.3v -> 0-1023/5*3.3=675 -> 65-85
#define min_adc 80
#define max_adc 1023
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
  return map(v, min_adc, max_adc, min_dimm, max_dimm);
}

void setup() {
  Serial.begin(9600);
  analogReference(EXTERNAL);

  for (int i = 0; i < NUM_CHANNELS; i++) {
    dimmers[i].begin(NORMAL_MODE, ON);
  }

  Serial.println("Dimmer controller ready.");
}

void loop() {

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

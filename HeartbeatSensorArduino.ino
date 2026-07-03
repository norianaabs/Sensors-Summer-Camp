#include <PulseSensorPlayground.h>

const int PulseWire = A0;
const int LED = LED_BUILTIN;
const int Threshold = 480;

PulseSensorPlayground pulseSensor;

int BPM = 0;
int IBI = 0;
int Beat = 0;

void setup() {
  Serial.begin(115200);

  pulseSensor.analogInput(PulseWire);
  pulseSensor.blinkOnPulse(LED);
  pulseSensor.setThreshold(Threshold);

  pulseSensor.begin();
}

void loop() {

  int Signal = analogRead(PulseWire);

  if (pulseSensor.sawStartOfBeat()) {
    BPM = pulseSensor.getBeatsPerMinute();
    IBI = pulseSensor.getInterBeatIntervalMs();
    Beat = 1023;
  } else {
    Beat = 0;
  }

  Serial.print(Signal);
  Serial.print(",");
  Serial.print(BPM);
  Serial.print(",");
  Serial.print(IBI);
  Serial.print(",");
  Serial.println(Beat);

  delay(10);
}
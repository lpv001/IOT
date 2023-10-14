#include "./telemetry.h"
#include "./cmd.h"
#include "./AvionicsReceive.h"


int value1 = 10;
int value2 = 100;
int value3 = 1000;

long previousTime = 0;
#define PERIOD 25
int period = 25;

void setup() {
imusetup();
//  startMPU();
  // put your setup code here, to run once:
Serial.begin(115200);
telemetryInitialise();
}

void loop() {
imuloop();
 if ((millis() - previousTime ) > period)
 {
  telemetryUpdate ();
  telemetryOutputSerial ();
  value1++;
  previousTime = millis();
 }
 processSerialData();
}

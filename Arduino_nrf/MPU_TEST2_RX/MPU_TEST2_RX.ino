#include<SPI.h>
#include<nRF24L01.h>
#include<RF24.h>
RF24 radio(9, 10);
const byte address[6] = "00001";
struct Package{
  int roll_rate , pitch_rate , yaw_rate ;
  int roll , pitch , yaw;
  float accelerometerX , accelerometerY , accelerometerZ ;
  int T, P , H;
}data;
void setup() {
  Serial.begin(115200);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.startListening();
}

void loop() {
  if (radio.available()>0)
  {
    radio.read(&data, sizeof(data));
    //Serial.print("T: ");
    Serial.print(data.T);
    Serial.print("       ");
    //Serial.print("P: ");
    Serial.print(data.P);
    Serial.print("       ");
    //Serial.print("H: ");
    Serial.print(data.H);
    Serial.print("       ");
    //Serial.print("dvX: ");
    Serial.print(data.accelerometerX);
    Serial.print("       ");
    //Serial.print("dvY: ");
    Serial.print(data.accelerometerY);
    Serial.print("       ");
    //Serial.print("dvZ: ");
    Serial.print(data.accelerometerZ);
    Serial.print("       ");
    //Serial.print("roll: ");
    Serial.print(data.roll);
    Serial.print("       ");
    //Serial.print("pitch: ");
    Serial.print(data.pitch);
    Serial.print("       ");
    //Serial.print("yaw: ");
    Serial.print(data.yaw);
    Serial.print("       ");
    //Serial.print("gyroX: ");
    Serial.print(data.roll_rate);
    Serial.print("       ");
    //Serial.print("gyroY: ");
    Serial.print(data.pitch_rate);
    Serial.print("       ");
    //Serial.print("gyroZ: ");
    Serial.println(data.yaw_rate);

    
    //total 12 datA
  }
}

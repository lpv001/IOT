#include<SPI.h>
#include<nRF24L01.h>
#include<RF24.h>
RF24 radio(9, 10);
const byte address[6] = "00001";
double H;
boolean me=false;
struct Package{
  double accXangle ,accYangle,acczangle ,gyroXrate ,gyroYrate,gyroZrate,T,P;
}test;
void setup() {
  Serial.begin(115200);
  radio.begin();
  radio.openWritingPipe(address);
  radio.stopListening();
  pinMode(0x02,OUTPUT);
  pinMode(0x03,OUTPUT);
}
void loop() {
  if(Serial.available()>0){
    char m= Serial.read();
    radio.write(&m,1);
    if(m=='2'){
      me= true;
    }
  }
  if (me == true){
    radio.openReadingPipe(0,address);
    radio.startListening();
    digitalWrite(0x02,HIGH);
    digitalWrite(0x03,HIGH);
  }
  if(radio.available()>0){
    radio.read(&test,sizeof(test));
  }
 calculate();
 printData();
}
void printData(){
 Serial.print("X: ");
 Serial.print(test.accXangle);
 Serial.print("        ");
 Serial.print("Y: ");
 Serial.print(test.accYangle);
 Serial.print("        ");
 Serial.print("Z: ");
 Serial.print(test.acczangle);
 Serial.print("        ");
 Serial.print("accX: ");
 Serial.print(test.gyroXrate);
 Serial.print("        ");
 Serial.print("accY: ");
 Serial.print(test.gyroYrate);
 Serial.print("        ");
 Serial.print("accZ: ");
 Serial.print(test.gyroZrate);
 Serial.print("        ");
 Serial.print("T: ");
 Serial.print(test.T);
 Serial.print("        ");
 Serial.print("P: ");
 Serial.print(test.P);
 Serial.print("        ");
 Serial.print("H: ");
 Serial.println(H);
}
void calculate(){
  H = 44330*(1-pow((test.P/1013.25),1/5.255));
}

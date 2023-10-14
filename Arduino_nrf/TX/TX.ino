#include<SPI.h>
#include<nRF24L01.h>
#include<RF24.h>

RF24 radio(9, 10);

const byte address[6] = "00001";
struct package {
  double a;
  int b;
} test;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  radio.begin();
  //Serial.println("Header \t \t \t Data1:\t \t");

  //set the address
  radio.openReadingPipe(0,address);
  radio.startListening();
  radio.openWritingPipe(address);

  //Set module as receiver
  radio.stopListening();
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if(Serial.available()>0){
    char m = Serial.read();
  //test.b=random(20);
  //test.a=random(40);
  //radio.write(&test, sizeof(test));
  //Serial.print(test.a);
  //Serial.print("       ");
  //Serial.println(test.b);
  radio.write(&m,1);
  }
}

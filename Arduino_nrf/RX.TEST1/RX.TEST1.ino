#include<SPI.h>
#include<nRF24L01.h>
#include<RF24.h>

int arrayy[12];
int count = 0;
RF24 radio(9, 10);
const byte address[6] = "00001";
struct package {
  int a;
  int b;
  int c;
  int d;
  int e;
  int f;
  int g;
  int h;
} test;


void setup() {

  // put your setup code here, to run once:
  Serial.begin(115200);
  radio.begin();
  //Serial.println("Header \t \t \t Data1:\t \t");
  //set the address
  radio.setChannel(85);
  radio.openWritingPipe(address);
  radio.openReadingPipe(0, address);
  //Set module as receiver
  radio.startListening();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (radio.available() > 0)
  {
    radio.read(&test, sizeof(test));

    if ( test.a == 10 ) {

      arrayy[0] = test.a;
      arrayy[1] = test.b;
      arrayy[2] = test.c;
      arrayy[3] = test.d;
      arrayy[4] = test.e;
      arrayy[5] = test.f;
      arrayy[6] = test.g;
      arrayy[7] = test.h;

    } else if ( test.a = 101 ) {
      arrayy[8] = test.a;
      arrayy[9] = test.b;
      arrayy[10] = test.c;
      arrayy[11] = test.d;
    }else{
      
    }
    Serial.print(arrayy[0]);
    Serial.print("\t");
    Serial.print(arrayy[1]);
    Serial.print("\t");
    Serial.print(arrayy[2]);
    Serial.print("\t");
    Serial.print(arrayy[3]);
    Serial.print("\t");
    Serial.print(arrayy[4]);
    Serial.print("\t");
    Serial.print(arrayy[5]);
    Serial.print("\t");
    Serial.print(arrayy[6]);
    Serial.print("\t");
    Serial.print(arrayy[7]);
    Serial.print("\t");
    Serial.print(arrayy[8]);
    Serial.print("\t");
    Serial.print(arrayy[9]);
    Serial.print("\t");
    Serial.print(arrayy[10]);
    Serial.print("\t");
    Serial.println(arrayy[11]);
  }
}

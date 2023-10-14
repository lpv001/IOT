#include<SPI.h>
#include<nRF24L01.h>
#include<RF24.h>

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

struct package1 {
  int a1;
  int b1;
  int c1;
  int d1;
} test1;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  radio.begin();
  //Serial.println("Header \t \t \t Data1:\t \t");
  //set the address
  radio.setChannel(85);
  radio.openReadingPipe(0,address);
  radio.startListening();
  radio.openWritingPipe(address);

  //Set module as receiver
  radio.stopListening();
}

void loop() {
  // put your main code here, to run repeatedly:

//  for ( int i = 0 ; i < 100 ; ++i ){
//    ++m;
//    delay(1);
//    if( m == 99 )
//      m = 0;
//  }
  test.a = 10;
  test.b = 20;
  test.c = 30;
  test.d = 40;
  test.e = 50;
  test.f = 60;
  test.g = 70;
  test.h = 80;
  test1.a1 = 101;
  test1.b1 = 201;
  test1.c1 = 301;
  test1.d1 = 401;


  radio.write(&test, sizeof(test));
  radio.write(&test1, sizeof(test1));
  //Serial.print("       ");

  
}

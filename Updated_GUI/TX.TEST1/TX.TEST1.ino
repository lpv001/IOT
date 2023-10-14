#include<SPI.h>
#include<nRF24L01.h>
#include<RF24.h>

RF24 radio(9, 10);

const byte address[6] = "00001";
struct package {
  double m;
  double acc_x, acc_y, acc_z;
  double angle_x, angle_y, angle_z ;
} test;

struct package1 {
  double m;
  double gyro_x, gyro_y, gyro_z ;
  double velocity, pressure, altitude;
} test1;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  radio.begin();
  //Serial.println("Header \t \t \t Data1:\t \t");
  //set the address
  //radio.setChannel(85);
  radio.openReadingPipe(0, address);
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
  test.m = 2021;
  test.acc_x = 10;
  test.acc_y = 20;
  test.acc_z = 30;
  test.angle_x = 40;
  test.angle_y = 50;
  test.angle_z = 60;



  test1.m = 2022;
  test1.gyro_x = 70;
  test1.gyro_y = 80;
  test1.gyro_z = 90;
  test1.pressure = 100;
  test1.velocity = 110;
  test1.altitude = 120;
  radio.write(&test, sizeof(test));
  radio.write(&test1, sizeof(test1));


  //Serial.print("       ");


}

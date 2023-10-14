#include<SPI.h>
#include<nRF24L01.h>
#include<RF24.h>
#include<Servo.h>
Servo servo;
RF24 radio(9, 10);
const byte address[6] = "00001";
struct package {
  double a;
  int b;
} test;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  servo.attach(5);
  radio.begin();
  //Serial.println("Header \t \t \t Data1:\t \t");

  //set the address
  radio.openReadingPipe(0, address);

  //Set module as receiver
  radio.startListening();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (radio.available()>0)
  {
    char m[32]={0};
    //radio.read(&test, sizeof(test));
    radio.read(&m,sizeof(m));
    for   (int i=0; i<32 ; i++){
    Serial.print(m[i]);

      if(m[i] == 'a'){
        servo.write(180);
      }else{
        servo.write(90);
      }

    
    }
    //Serial.print(test.a);
    //Serial.print("       ");
    //Serial.println(test.b);
  }
}

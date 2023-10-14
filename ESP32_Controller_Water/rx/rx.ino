#include <SoftwareSerial.h>
SoftwareSerial arduino(A5, A4);
unsigned int x ;
int count = 0;
bool state = true;

int a[8];
bool c1, c2, c3, c4, c5, c6, c7, c8;

void setup() {
  Serial.begin(115200);
  pinMode(0x02, OUTPUT);
  pinMode(0x03, OUTPUT);
  pinMode(0x04, OUTPUT);
  pinMode(0x05, OUTPUT);
  pinMode(0x06, OUTPUT);
  pinMode(0x07, OUTPUT);
  pinMode(0x08, OUTPUT);
  pinMode(0x09, OUTPUT);
  
  arduino.begin(115200);
  digitalWrite(0x02, LOW);
  digitalWrite(0x03, LOW);
  digitalWrite(0x04, LOW);
  digitalWrite(0x05, LOW);
  digitalWrite(0x06, LOW);
  digitalWrite(0x07, LOW);
  digitalWrite(0x08, LOW);
  digitalWrite(0x09, LOW);
  
}

void loop() {

  while ( arduino.available() ) {
    x = arduino.read();
    Serial.println(x);
    for ( int i = 0 ; x > 0 ; ++i ) {
      a[i] = x % 2;
      x = x / 2;
    }

    if ( a[0] == 1 ) {
      c1 = true;
    } else {
      c1 = false;
    }

    if ( a[1] == 1 ) {
      c2 = true;
    } else {
      c2 = false;
    }

    if ( a[2] == 1 ) {
      c3 = true;
    } else {
      c3 = false;
    }

    if ( a[3] == 1 ) {
      c4 = true;
    } else {
      c4 = false;
    }

    if ( a[4] == 1 ) {
      c5 = true;
    } else {
      c5 = false;
    }

    if ( a[5] == 1 ) {
      c6 = true;
    } else {
      c6 = false;
    }

    if ( a[6] == 1 ) {
      c7 = true;
    } else {
      c7 = false;
    }

    if ( a[7] == 1 ) {
      c8 = true;
    } else {
      c8 = false;
    }

    writing(c1, c2, c3, c4, c5, c6, c7, c8);



    //    if ( x == 127 ) {
    //      if ( state == true ) {
    //        close_all();
    //        state = false;
    //      }
    //      ++count;
    //    } else {
    //      count = 0;
    //      state = true;
    //    }
    //
    //    if ( count == 30 ) {
    //      do_something();
    //    }




    for ( int i = 0 ; i < 8 ; ++i ) {
      a[i] = 0;
    }

  }



}

void writing(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8) {
  digitalWrite(0x02, a1);
  digitalWrite(0x03, a2);
  digitalWrite(0x04, a3);
  digitalWrite(0x05, a4);
  digitalWrite(0x06, a5);
  digitalWrite(0x07, a6);
  digitalWrite(0x08, a7);
  digitalWrite(0x09, a8);
}

void do_something() {

}

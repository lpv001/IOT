#include <SoftwareSerial.h>

SoftwareSerial HC12(4, 5); 

int arr_lenght = 49;
byte container[41];

typedef union 
{
  float value;
  uint8_t bytes[4];
} strike;


void setup() {
  Serial.begin(9600);             
  HC12.begin(9600);               
  digitalWrite(3, LOW);
}

void loop() {
  strike a;
  strike b;
  strike c;
  strike d;
  strike e;
  strike f;
  strike g;
  strike h;
  strike i;
  strike j;
  strike k;
  strike l;

  a.value = 3.14;
  b.value = 4.13;
  c.value = 7.77;
  d.value = 8.88;
  e.value = 9.99;
  f.value = 10.12;
  g.value = 20.2;
  h.value = 30.3;
  i.value = 99.9;
  j.value = 903000.9;
  k.value = 233.3;
  l.value = 360.3;

  for ( int i = 0 ; i < arr_lenght ; ++i ){
    container[i] = 0x00;
  }

  container[0] = 'H';
  
  container[1] = a.bytes[0];
  container[2] = a.bytes[1];
  container[3] = a.bytes[2];
  container[4] = a.bytes[3];

  container[5] = b.bytes[0];
  container[6] = b.bytes[1];
  container[7] = b.bytes[2];
  container[8] = b.bytes[3];

  container[9] = c.bytes[0];
  container[10] = c.bytes[1];
  container[11] = c.bytes[2];
  container[12] = c.bytes[3];

  container[13] = d.bytes[0];
  container[14] = d.bytes[1];
  container[15] = d.bytes[2];
  container[16] = d.bytes[3];
  
  container[17] = e.bytes[0];
  container[18] = e.bytes[1];
  container[19] = e.bytes[2];
  container[20] = e.bytes[3];

  container[21] = f.bytes[0];
  container[22] = f.bytes[1];
  container[23] = f.bytes[2];
  container[24] = f.bytes[3];

  container[25] = g.bytes[0];
  container[26] = g.bytes[1];
  container[27] = g.bytes[2];
  container[28] = g.bytes[3];

  container[29] = h.bytes[0];
  container[30] = h.bytes[1];
  container[31] = h.bytes[2];
  container[32] = h.bytes[3];

  container[33] = i.bytes[0];
  container[34] = i.bytes[1];
  container[35] = i.bytes[2];
  container[36] = i.bytes[3];

  container[37] = j.bytes[0];
  container[38] = j.bytes[1];
  container[39] = j.bytes[2];
  container[40] = j.bytes[3];

//  container[41] = k.bytes[0];
//  container[42] = k.bytes[1];
//  container[43] = k.bytes[2];
//  container[44] = k.bytes[3];
//
//  container[45] = l.bytes[0];
//  container[46] = l.bytes[1];
//  container[47] = l.bytes[2];
//  container[48] = l.bytes[3];
  
  
  for ( int i = 0 ; i < arr_lenght ; ++i ){
    HC12.write(container[i]);
  }
 
}

#include <SoftwareSerial.h>
#define ll long long

SoftwareSerial HC12(4, 5);


int pin = 0;
uint8_t container[128];
int currentIndex ;
int tlm_length = 41;

void setup() {
  Serial.begin(9600);
  HC12.begin(9600);
  digitalWrite(13, LOW);
}

void loop() {

  processReadingData();

}

void processReadingData() {
  uint8_t data;
  boolean start;
  while ( HC12.available() ) {
    data = HC12.read();
    start = addData((uint8_t)data);
  }
  if ( start ) {
    processData();
  }
}

boolean addData(byte nextChar) {
  
  if (pin == 1)
  {
    container[currentIndex] = nextChar;
    currentIndex++;

    if (currentIndex == tlm_length)
    {
      currentIndex = 0;
      pin = 0;
      return true;
    }
  }

  if (nextChar == 'H' && pin == 0)
  {
    container[currentIndex] = nextChar;
    pin = 1;
    currentIndex++;
  }
  return false;
}

void processData() {
  long m0 = (ll)container[4] << 24 | (ll)container[3] << 16 | (ll)container[2] << 8 | (ll)container[1];
  long m1 = (ll)container[8] << 24 | (ll)container[7] << 16 | (ll)container[6] << 8 | (ll)container[5];
  long m2 = (ll)container[12] << 24 | (ll)container[11] << 16 | (ll)container[10] << 8 | (ll)container[9];
  long m3 = (ll)container[16] << 24 | (ll)container[15] << 16 | (ll)container[14] << 8 | (ll)container[13];
  long m4 = (ll)container[20] << 24 | (ll)container[19] << 16 | (ll)container[18] << 8 | (ll)container[17];
  long m5 = (ll)container[24] << 24 | (ll)container[23] << 16 | (ll)container[22] << 8 | (ll)container[21];
  long m6 = (ll)container[28] << 24 | (ll)container[27] << 16 | (ll)container[26] << 8 | (ll)container[25];
  long m7 = (ll)container[32] << 24 | (ll)container[31] << 16 | (ll)container[30] << 8 | (ll)container[29];
  long m8 = (ll)container[36] << 24 | (ll)container[35] << 16 | (ll)container[34] << 8 | (ll)container[33];
  long m9 = (ll)container[40] << 24 | (ll)container[39] << 16 | (ll)container[38] << 8 | (ll)container[37];
//  long m10 = (ll)container[44] << 24 | (ll)container[43] << 16 | (ll)container[42] << 8 | (ll)container[41];
//  long m11 = (ll)container[48] << 24 | (ll)container[47] << 16 | (ll)container[46] << 8 | (ll)container[45];
// 
  
  union
  {
    long y;
    double z;
  } data0, data1, data2, data3, data4, data5, data6, data7, data8, data9, data10, data11;
  data0.y = m0;
  data1.y = m1;
  data2.y = m2;
  data3.y = m3;
  data4.y = m4;
  data5.y = m5;
  data6.y = m6;
  data7.y = m7;
  data8.y = m8;
  data9.y = m9;
//  data10.y = m10;
//  data11.y = m11;
  Serial.print(data0.z);
  Serial.print("\t");
  Serial.print(data1.z);
  Serial.print("\t");
  Serial.print(data2.z);
  Serial.print("\t");
  Serial.print(data3.z);
  Serial.print("\t");
  Serial.print(data4.z);
  Serial.print("\t");
  Serial.print(data5.z);
  Serial.print("\t");
  Serial.print(data6.z);
  Serial.print("\t");
  Serial.print(data7.z);
  Serial.print("\t");
  Serial.print(data8.z);
  Serial.print("\t");
  Serial.println(data9.z);
//  Serial.print("\t");
//  Serial.print(data10.z);
//  Serial.print("\t");
//  Serial.println(data11.z);
  
}

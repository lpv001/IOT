#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#define ll long long


File myFile;
uint8_t bytes[4];
double result[8];
int counter = 0;

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  Wire.begin(8);
  Wire.onReceive(coming);
  
}

void loop()
{
  
  
}

void coming() {

  for (int x = 0 ; x < 4 ; x++) {
    bytes[x] = Wire.read();
  }

  ll m = (ll)bytes[3] << 24 | (ll)bytes[2] << 16 | (ll)bytes[1] << 8 | (ll)bytes[0];


  union
  {
    ll y;
    double z;
  } data;
  data.y = m;
//Serial.println(data.z);

  result[counter] = data.z;
  if (counter == 8 ) {
  Serial.print(result[0]);
  Serial.print("\t");
  Serial.print(result[1]);
  Serial.print("\t");
  Serial.print(result[2]);
  Serial.print("\t");
  Serial.print(result[3]);
  Serial.print("\t");
  Serial.print(result[4]);
  Serial.print("\t");
  Serial.print(result[5]);
  Serial.print("\t");
  Serial.print(result[6]);
  Serial.print("\t");
  Serial.print(result[7]);
  Serial.println("\t");

  
  
  counter = 0;
  }


  
 counter++;
}

#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#define ll long long


File myFile;
uint8_t bytes[4];
double result[13];
int counter = 0;
bool start = false;

double acc_x, acc_y, acc_z;
double angle_x, angle_y, angle_z ;
double gyro_x, gyro_y, gyro_z ;
double velocity, pressure, altitude;

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  Wire.begin(8);
  Wire.onReceive(coming);
  if (!SD.begin(10)) {
    Serial.println("Card failed, or not present");
    return;
  }else{
    Serial.println("Okay");
  }
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

if ( data.z > 1000 ){
  start = true;
}

if ( start == true ){
  

  result[counter] = data.z;
  if (counter == 12 ) {

  acc_x = result[12];
  acc_y = result[1];
  acc_z = result[8];
  angle_x = result[2];
  angle_y = result[3];
  angle_z = result[4];
  gyro_x = result[5];
  gyro_y = result[6];
  gyro_z = result[7];
  velocity = result[9];
  pressure = result[10];
  altitude = result[11];
  
  

  Serial.print(result[1]);
  Serial.print("\t  ");
  Serial.print(result[2]);
  Serial.print("\t  ");
  Serial.print(result[3]);
  Serial.print("\t  ");
  Serial.print(result[4]);
  Serial.print("\t  ");
  Serial.print(result[5]);
  Serial.print("\t  ");
  Serial.print(result[6]);
  Serial.print("\t  ");
  Serial.print(result[7]);
  Serial.print("\t  ");
  Serial.print(result[8]);
  Serial.print("\t  ");
  Serial.print(result[9]);
  Serial.print("\t  ");
  Serial.print(result[10]);
  Serial.print("\t  ");
  Serial.print(result[11]);
  Serial.print("\t  ");
  Serial.print(result[12]);
  Serial.println("\t");
////
//Serial.print(velocity);
//Serial.print("\t");
//Serial.print(pressure);
//Serial.print("\t");
//Serial.println(altitude);

  File dataFile = SD.open("data.txt", FILE_WRITE);
  if (dataFile)
  {
  dataFile.print(acc_x);
  dataFile.print("\t");
  dataFile.print(acc_y);
  dataFile.print("\t");
  dataFile.print(acc_z);
  dataFile.print("\t");
  dataFile.print(angle_x);
  dataFile.print("\t");
  dataFile.print(angle_y);
  dataFile.print("\t");
  dataFile.print(angle_z);
  dataFile.print("\t");
  dataFile.print(gyro_x);
  dataFile.print("\t");
  dataFile.print(gyro_y);
  dataFile.print("\t");
  dataFile.print(gyro_z);
  dataFile.print("\t");
  dataFile.print(velocity);
  dataFile.print("\t");
  dataFile.print(altitude);
  dataFile.print("\t");
  dataFile.print(pressure);
  dataFile.println("\t");
  dataFile.close();
  //Serial.println("Done");
  }
  
  counter = 0;
  }

}

 counter++;
}

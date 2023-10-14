#include<Wire.h>
#define ADDRESS_SENSOR 0x77
float AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
float pitch_gyro , roll_gyro;
float gyrox_calibration , gyroy_calibration, gyroz_calibration;
float pitch_acc , roll_acc , delta_acc;
long loop_timer;
struct Package {
  int roll_rate , pitch_rate , yaw_rate ;
  int roll , pitch , yaw;
  float accelerometerX , accelerometerY , accelerometerZ ;
} data;

void setup()
{
  Serial.begin(115200);
  Wire.begin();
  //reg();
  for (int i = 0 ; i < 2000 ; i++) {
    startMPU();
    GyX = (GyX / 65.5) * 0.01745;
    GyY = (GyY / 65.5) * 0.01745;
    GyZ = (GyZ / 65.5) * 0.01745;
    gyrox_calibration += GyX;
    gyroy_calibration += GyY;
    gyroz_calibration += GyZ;
    delay(3);
  }

  gyrox_calibration /= 2000;
  gyroy_calibration /= 2000;
  gyroz_calibration /= 2000;
  loop_timer = micros();
}


//Data we want :roll,pitch,yaw,roll_acc,pitch_acc,delta_acc,accelerometerX ... total 9



void loop()
{
  startMPU();

  // --------------------------------------------------------------------------------------------------------------------------------------------------------------------
  data.accelerometerX = AcX / 8192 ; //AccelScaleFactor equal to 8192
  data.accelerometerY = AcY / 8192 ;
  data.accelerometerZ = AcZ / 8192 ;
  GyX = (GyX / 65.5) * 0.01745; //GyroScaleFactor 65.5 , 1 deg = 0.01745rad
  GyY = (GyY / 65.5) * 0.01745;
  GyZ = (GyZ / 65.5) * 0.01745;
  GyX -= gyrox_calibration;
  GyY -= gyroy_calibration;
  GyZ -= gyroz_calibration;
  // --------------------------------------------------------------------------------------------------------------------------------------------------------------------


  roll_acc = atan2(AcY, sqrt(AcX * AcX + AcZ * AcZ)) * 57.324;
  pitch_acc = atan2(AcX, sqrt(AcY * AcY + AcZ * AcZ)) * 57.324;
  delta_acc = atan2(sqrt(AcX * AcX + AcY * AcY), AcZ) * 57.324;

  data.roll_rate = GyX + GyY * sin(roll_acc) * tan(pitch_acc) + GyZ * cos(roll_acc) * tan(pitch_acc);
  data.pitch_rate = GyY * cos(roll_acc) - GyZ * sin(roll_acc);
  data.yaw_rate = GyY * sin(roll_acc) * (1 / cos(pitch_acc)) + GyZ * cos(roll_acc) * (1 / cos(pitch_acc));


  roll_gyro += data.roll_rate / 250 * 57.324;
  pitch_gyro += data.pitch_rate / 250 * 57.324;
  data.yaw += data.yaw_rate / 250 * 57.296 ;              // yaw angle has some problem

  data.roll = 0.98 * roll_gyro + 0.02 * roll_acc ;
  data.pitch = 0.98 * pitch_gyro + 0.02 * pitch_acc ;


  data.roll = roll_acc;
  data.pitch = pitch_acc;

  Serial.print(data.roll);
  Serial.print("\t");
  Serial.print(data.pitch);
  Serial.print("\t");
  Serial.println(data.yaw);


  while (micros() - loop_timer < 4000);
  loop_timer = micros();
}

void reg() {
  Wire.beginTransmission(0x68);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission();
  Wire.beginTransmission(0x68);
  Wire.write(0x1C);
  Wire.write(0x10);
  Wire.endTransmission();
  Wire.beginTransmission(0x68);
  Wire.write(0x1B);
  Wire.write(0x08);
  Wire.endTransmission();
}

void startMPU() {
  Wire.beginTransmission(0x68);
  Wire.write(0x3B);
  Wire.endTransmission();
  Wire.requestFrom(0x68, 14);
  while (Wire.available() < 14);
  AcX = Wire.read() << 8 | Wire.read();
  AcY = Wire.read() << 8 | Wire.read();
  AcZ = Wire.read() << 8 | Wire.read();
  Tmp = Wire.read() << 8 | Wire.read();
  GyX = Wire.read() << 8 | Wire.read();
  GyY = Wire.read() << 8 | Wire.read();
  GyZ = Wire.read() << 8 | Wire.read();
}

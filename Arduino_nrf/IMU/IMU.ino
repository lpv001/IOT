#include<Wire.h>
const int MPU=0x68;  // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
double compAngleX,compAngleY,/*gzangle,*/compAnglez,timer;
  double accXangle ,accYangle,acczangle ,gyroXrate ,gyroYrate,gyroZrate;
  double gyroXAngle, gyroYAngle, gyroZAngle;
  // float rgyro,w;
  int ap=0.955;

  

  void setup()
{
   Serial.begin(115200);
/////////////////////// SENSOR READING//////////
 Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  
  ///////////////////////////////////////
}
void loop()
{

  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,14,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)   
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)



 accXangle = (atan2(AcY, AcZ) * RAD_TO_DEG);
 accYangle = (atan2(AcX, AcZ) * RAD_TO_DEG);
acczangle = (atan2(AcX,AcY) * RAD_TO_DEG);/* my attempt to calculate yaw but not correct*/
 gyroXrate = GyX / 16.5;
 gyroYrate = GyY / 16.5;
 gyroZrate = GyZ/ 16.5;
 Tmp=(Tmp/340+36.53);

 Serial.print("Temp : ");
 Serial.print(Tmp);
 Serial.print("       ");
 Serial.print("X: ");
 Serial.print(accXangle);
 Serial.print("        ");
 Serial.print("Y: ");
 Serial.print(accYangle);
 Serial.print("        ");
 Serial.print("Z: ");
 Serial.print(acczangle);
 Serial.print("        ");
 Serial.print("accX: ");
 Serial.print(gyroXrate);
 Serial.print("        ");
 Serial.print("accY: ");
 Serial.print(gyroYrate);
 Serial.print("        ");
 Serial.print("accZ: ");
 Serial.print(gyroZrate);
 Serial.print("        ");
 Serial.print("gX: ");
 Serial.print(GyX);
 Serial.print("        ");
 Serial.print("gY: ");
 Serial.print(GyY);
 Serial.print("        ");
 Serial.print("gZ: ");
 Serial.println(GyZ);
 delay(100);
 
}

#include<Wire.h>
#define ADDRESS_SENSOR 0x77 
float AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
float pitch_acc , roll_acc , delta_acc;
float roll_rate , pitch_rate , yaw_rate ;
float pitch_gyro , roll_gyro;
float roll , pitch , yaw;
float gyrox_calibration ,gyroy_calibration,gyroz_calibration;
float accelerometerX , accelerometerY , accelerometerZ ;
long loop_timer;

int16_t  ac1, ac2, ac3, b1, b2, mb, mc, md;
uint16_t ac4, ac5, ac6;
const uint8_t oss = 3;
const uint8_t osd = 26;
float T, P, H;


  void setup()
{
  Serial.begin(115200);
  Wire.begin();
  reg();
  ac1 = read_2_bytes(0xAA);
  ac2 = read_2_bytes(0xAC);
  ac3 = read_2_bytes(0xAE);
  ac4 = read_2_bytes(0xB0);
  ac5 = read_2_bytes(0xB2);
  ac6 = read_2_bytes(0xB4);
  b1  = read_2_bytes(0xB6);
  b2  = read_2_bytes(0xB8);
  mb  = read_2_bytes(0xBA);
  mc  = read_2_bytes(0xBC);
  md  = read_2_bytes(0xBE);
  
   for (int i=0 ; i<2000 ; i++){
 startMPU();
 GyX=(GyX/65.5)*0.01745;  
 GyY=(GyY/65.5)*0.01745;
 GyZ=(GyZ/65.5)*0.01745;
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
accelerometerX = AcX/8192 ;  //AccelScaleFactor equal to 8192
accelerometerY = AcY/8192 ;
accelerometerZ = AcZ/8192 ;
GyX=(GyX/65.5)*0.01745;  //GyroScaleFactor 65.5 , 1 deg = 0.01745rad
GyY=(GyY/65.5)*0.01745;
GyZ=(GyZ/65.5)*0.01745;
GyX -= gyrox_calibration;
GyY -= gyroy_calibration;
GyZ -= gyroz_calibration;
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------


roll_acc = atan2(AcY,sqrt(AcX*AcX + AcZ*AcZ))*57.324;
pitch_acc = atan2(AcX,sqrt(AcY*AcY + AcZ*AcZ))*57.324;
delta_acc = atan2(sqrt(AcX*AcX + AcY*AcY),AcZ)*57.324;

roll_rate = GyX + GyY*sin(roll_acc)*tan(pitch_acc) + GyZ*cos(roll_acc)*tan(pitch_acc);
pitch_rate = GyY*cos(roll_acc) - GyZ*sin(roll_acc);
yaw_rate = GyY*sin(roll_acc)*(1/cos(pitch_acc)) + GyZ*cos(roll_acc)*(1/cos(pitch_acc));


roll_gyro += roll_rate/250 * 57.324;
pitch_gyro += pitch_rate/250 * 57.324;
yaw += yaw_rate/250 * 57.296 ;                // yaw angle has some problem

roll = 0.98*roll_gyro + 0.02*roll_acc ;
pitch = 0.98*pitch_gyro + 0.02*pitch_acc ;


roll = roll_acc;
pitch = pitch_acc;

 int32_t b5;
 b5 = temperature();
 P = pressure(b5);
 H = 44330*(1-pow((P/1013.25),1/5.255));

//Serial.println(P);
Serial.println(roll);

while(micros() - loop_timer < 4000);                              
  loop_timer = micros();
}


void reg(){
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
void startMPU(){
  Wire.beginTransmission(0x68);                                        
  Wire.write(0x3B);                                                    
  Wire.endTransmission();                                             
  Wire.requestFrom(0x68,14);                                          
  while(Wire.available() < 14);  
  AcX=Wire.read()<<8|Wire.read();    
  AcY=Wire.read()<<8|Wire.read(); 
  AcZ=Wire.read()<<8|Wire.read();  
  Tmp=Wire.read()<<8|Wire.read();  
  GyX=Wire.read()<<8|Wire.read();  
  GyY=Wire.read()<<8|Wire.read();  
  GyZ=Wire.read()<<8|Wire.read();
}

double pressure(int32_t b5)
{
  int32_t x1, x2, x3, b3, b6, p, UP;
  uint32_t b4, b7; 

  UP = read_pressure();                         

  b6 = b5 - 4000;
  x1 = (b2 * (b6 * b6 >> 12)) >> 11; 
  x2 = ac2 * b6 >> 11;
  x3 = x1 + x2;
  b3 = (((ac1 * 4 + x3) << oss) + 2) >> 2;
  x1 = ac3 * b6 >> 13;
  x2 = (b1 * (b6 * b6 >> 12)) >> 16;
  x3 = ((x1 + x2) + 2) >> 2;
  b4 = (ac4 * (uint32_t)(x3 + 32768)) >> 15;
  b7 = ((uint32_t)UP - b3) * (50000 >> oss);
  if(b7 < 0x80000000) { p = (b7 << 1) / b4; } else { p = (b7 / b4) << 1; } 
  x1 = (p >> 8) * (p >> 8);
  x1 = (x1 * 3038) >> 16;
  x2 = (-7357 * p) >> 16;
  return (p + ((x1 + x2 + 3791) >> 4)) / 100.0f; 
}


int32_t temperature()
{
  int32_t x1, x2, b5, UT;

  Wire.beginTransmission(ADDRESS_SENSOR); 
  Wire.write(0xf4);                       
  Wire.write(0x2e);                       
  Wire.endTransmission();                 
  delay(5);                               
  
  UT = read_2_bytes(0xf6);                
  x1 = (UT - (int32_t)ac6) * (int32_t)ac5 >> 15;
  x2 = ((int32_t)mc << 11) / (x1 + (int32_t)md);
  b5 = x1 + x2;
  T  = (b5 + 8) >> 4;
  T = T / 10.0;                            
  return b5;  
}


int32_t read_pressure()
{
  int32_t value; 
  Wire.beginTransmission(ADDRESS_SENSOR);   
  Wire.write(0xf4);                         
  Wire.write(0x34 + (oss << 6));            
  Wire.endTransmission();                  
  delay(osd);                               
  Wire.beginTransmission(ADDRESS_SENSOR);
  Wire.write(0xf6);                         
  Wire.endTransmission();
  Wire.requestFrom(ADDRESS_SENSOR, 3);      
  if(Wire.available() >= 3)
  {
    value = (((int32_t)Wire.read() << 16) | ((int32_t)Wire.read() << 8) | ((int32_t)Wire.read())) >> (8 - oss);
  }
  return value;                            
}


uint8_t read_1_byte(uint8_t code)
{
  uint8_t value;
  Wire.beginTransmission(ADDRESS_SENSOR);         
  Wire.write(code);                               
  Wire.endTransmission();                         
  Wire.requestFrom(ADDRESS_SENSOR, 1);            
  if(Wire.available() >= 1)
  {
    value = Wire.read();                          
  }
  return value;                                   
}


uint16_t read_2_bytes(uint8_t code)
{
  uint16_t value;
  Wire.beginTransmission(ADDRESS_SENSOR);         
  Wire.write(code);                               
  Wire.endTransmission();                         
  Wire.requestFrom(ADDRESS_SENSOR, 2);            
  if(Wire.available() >= 2)
  {
    value = (Wire.read() << 8) | Wire.read();     
  }
  return value;                                   
}

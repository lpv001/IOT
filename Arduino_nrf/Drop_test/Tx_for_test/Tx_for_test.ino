#include <Wire.h>



float  acc_total_vector;
float gyro_x_cal, gyro_y_cal, gyro_z_cal;
float gyro_z_old, yaw_old, driftz;
float temperature;
long loop_timer;
float pitch, roll;
boolean set_gyro_angles;
float roll_acc, pitch_acc;
float roll_acc_cal, pitch_acc_cal;
float pitch_gyro, roll_gyro;
int R = 1000; 
int H = 1; 
float Q = 0.09; 
float P = 0;
float K = 0; 
float u_hat = 0; 
float u;
struct Package{
  float pitch_output, roll_output, yaw, gyro_x, gyro_y, gyro_z, acc_x, acc_y, acc_z;
}test;
void setup() 
{
                                                          
  Serial.begin(115200);                                               
  Wire.begin();                                                                                                  
  setup_mpu_6050_registers();                                          
                                    

  for (int cal_int = 0; cal_int < 2000 ; cal_int ++){                 
    read_mpu_6050_data();                                              
    test.gyro_x = test.gyro_x/65.5*0.01745;
    test.gyro_y = test.gyro_y/65.5*0.01745;
    KALMAN(test.gyro_z);
    gyro_x_cal += test.gyro_x;                                              
    gyro_y_cal += test.gyro_y;                                              
    gyro_z_cal += u_hat;                                                
    delay(3);                                                          
  }
  gyro_x_cal /= 2000;                                                 
  gyro_y_cal /= 2000;                                                  
  gyro_z_cal /= 2000;                                                  
  gyro_z_old =0;
  read_mpu_6050_data();
  acc_total_vector = sqrt((test.acc_x*test.acc_x)+(test.acc_y*test.acc_y)+(test.acc_z*test.acc_z));  
  pitch_acc_cal = asin((float)test.acc_x/acc_total_vector)* 57.296;       
  roll_acc_cal = asin((float)test.acc_y/acc_total_vector)* 57.296;                                                    
  loop_timer = micros();                                               

}

void loop()
{
  read_mpu_6050_data();                                                
  test.gyro_x = test.gyro_x/65.5*0.01745;
  test.gyro_y = test.gyro_y/65.5*0.01745;
  test.gyro_x -= gyro_x_cal;                                                
  test.gyro_y -= gyro_y_cal;                                               
  test.gyro_z -= gyro_z_cal;                                                
  KALMAN(test.gyro_z);
  pitch_gyro += (test.gyro_y / 250) * 57.296;                                   
  roll_gyro += (test.gyro_x / 250) * 57.296;                                    
  test.yaw += ((u_hat/65.5*0.01745) / 250) * 57.296;
  if (abs(u_hat-gyro_z_old)<=P)
  {
    driftz = test.yaw-yaw_old;
    if(abs(test.yaw-yaw_old) <= 0.001)
    {
      test.yaw -= driftz;           
    }
  }
  yaw_old = test.yaw;                  
  gyro_z_old = u_hat;            
  acc_total_vector = sqrt((test.acc_x*test.acc_x)+(test.acc_y*test.acc_y)+(test.acc_z*test.acc_z));  
  pitch_acc = atan2(test.acc_x,test.acc_z)*57.296;
  roll_acc = atan2(test.acc_y,test.acc_z)*57.296;
  pitch_acc -= pitch_acc_cal;                         
  roll_acc -= roll_acc_cal;                           
  if(set_gyro_angles){                                               
    pitch = pitch_gyro * 0.98 + pitch_acc * 0.02;     
    roll = roll_gyro * 0.98 + roll_acc * 0.02;        
  }
  else{                                              
    pitch = pitch_acc;                               
    roll = roll_acc;                                  
    set_gyro_angles = true;                           
  }
  test.pitch_output = test.pitch_output * 0.7 + pitch * 0.3;    
  test.roll_output = test.roll_output * 0.7 + roll * 0.3;      
  pitch_gyro = test.pitch_output;
  roll_gyro = test.roll_output;
  Serial.print("Roll : ");
  Serial.print(test.roll_output);
  Serial.print(", Pitch : ");
  Serial.print(test.pitch_output);
  Serial.print(", Yaw : ");
  Serial.println(test.yaw);
  while(micros() - loop_timer < 4000);                                 
  loop_timer = micros();                                               
}
void read_mpu_6050_data()
{                                                                     
  Wire.beginTransmission(0x68);                                        
  Wire.write(0x3B);                                                    
  Wire.endTransmission();                                              
  Wire.requestFrom(0x68,14);                                          
  while(Wire.available() < 14);                                       
  test.acc_x = Wire.read()<<8|Wire.read();                                  
  test.acc_y = Wire.read()<<8|Wire.read();                                 
  test.acc_z = Wire.read()<<8|Wire.read();                                  
  temperature = Wire.read()<<8|Wire.read();                            
  test.gyro_x = Wire.read()<<8|Wire.read();                                 
  test.gyro_y = Wire.read()<<8|Wire.read();                                 
  test.gyro_z = Wire.read()<<8|Wire.read();                                
}
void setup_mpu_6050_registers()
{
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

void KALMAN(float u)
{
  K = P*H/(H*P*H+R);
  u_hat += K*(u - H * u_hat);
  P = (1 - K*H)*P + Q; 
}

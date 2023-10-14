#include<SPI.h>
#include<nRF24L01.h>
#include<RF24.h>
#include "./AvionicsReceive.h"
RF24 radio(9, 10);
const byte address[6] = "00001";

double arrayy[12];

struct package {
  double m;
  double acc_x, acc_y, acc_z;
  double angle_x, angle_y, angle_z ;

} data_i,data1;

struct package1 {
  double m;
  double gyro_x, gyro_y, gyro_z ;
  double velocity, pressure, altitude;
} data2;


void imusetup() {

  radio.begin();
  radio.openReadingPipe(0, address);
  radio.startListening();
}

void imuloop() {
  //int a[2][101];
  //
  //    for(int j = 0 ; j < 100 ; j++){
  //      a[0][j] = j;
  //    }
  //    for(int i = 100 ; i > 0 ; i--){
  //      a[1][i] = 100 - i;
  //    }
  //
  //  if( counter < 99 ) {
  //    counter++;
  //  }else{
  //    counter = 0;
  //    m += 1;
  //  }
  //
  //  if( m % 2 == 0){
  //    t = 1;
  //  }else{
  //    t = 0;
  //  }
  //
  //  data.yaw = a[t][counter];
  //  data.accelerometerX = a[t][counter] - 10 ;
  //  data.pitch_rate = a[t][counter] - 5;
  //
  //  int m;
  //  int k;
  //  m = 500*sin(2*3.14*0.05*a[t][counter] + 0);
  //  k = 1000*cos(2*3.14*0.05*a[t][counter] + 0);
  //  data.H = m;
  //  data.P = k;
  //  delay(10);


  if (radio.available() > 0)
  {
    int k;
    radio.read(&data_i, sizeof(data_i));
    k = (int) data_i.m;
    if ( k == 2021 ) {
      arrayy[0] = data_i.acc_x;
      arrayy[1] = data_i.acc_y;
      arrayy[2] = data_i.acc_z;
      arrayy[3] = data_i.angle_x;
      arrayy[4] = data_i.angle_y;
      arrayy[5] = data_i.angle_z;
    }
    else if ( k == 2022 ) {
      arrayy[6] = data_i.acc_x;
      arrayy[7] = data_i.acc_y;
      arrayy[8] = data_i.acc_z;
      arrayy[9] = data_i.angle_x;
      arrayy[10] = data_i.angle_y;
      arrayy[11] = data_i.angle_z;
    }

    data1.acc_x = arrayy[0];
    data1.acc_y = arrayy[1];
    data1.acc_z = arrayy[2];
    data1.angle_x = arrayy[3];
    data1.angle_y = arrayy[4];
    data1.angle_z = arrayy[5];
    data2.gyro_x = arrayy[6];
    data2.gyro_y = arrayy[7];
    data2.gyro_z = arrayy[8];
    data2.pressure = arrayy[9];
    data2.velocity = arrayy[10];
    data2.altitude = arrayy[11];


  }
}

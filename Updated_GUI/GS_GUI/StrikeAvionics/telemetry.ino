#include "./telemetry.h"
#include "./AvionicsReceive.h"

byte strikeTlm[tlm_length];
//MPU6050
STRIKE_t accX;
STRIKE_t accY;
STRIKE_t accZ;

STRIKE_t gyroX;
STRIKE_t gyroY;
STRIKE_t gyroZ;

STRIKE_t angleX;
STRIKE_t angleY;
STRIKE_t angleZ;

//BMP180
STRIKE_t pressure;
STRIKE_t alttitude;
STRIKE_t velocity;

////GPS
//STRIKE_t longitude;
//STRIKE_t latitude;



void telemetryInitialise(void)
{
  for (int i = 0; i < tlm_length; i++)
  {
    strikeTlm[i] = 0x00;
  }
}

void telemetryUpdate(void) {

  accX.value = data1.acc_x;
  accY.value = data1.acc_y;
  accZ.value = data1.acc_z;

  gyroX.value = data2.gyro_x;
  gyroY.value = data2.gyro_y;
  gyroZ.value = data2.gyro_z;

  angleX.value = data1.angle_x;
  angleY.value = data1.angle_y;
  angleZ.value = data1.angle_z;

  pressure.value = data2.pressure;
  alttitude.value = data2.altitude;
  velocity.value = data2.velocity;

//  longitude.value = random(0, 20);
//  latitude.value = random(0, 10);



  strikeTlm[tlm_h0] = 'H';
  strikeTlm[1] = cmdCounter;
  strikeTlm[2] = cmdBuffer[0];
  strikeTlm[3] = cmdBuffer[1];
  strikeTlm[4] = value1;
  strikeTlm[5] = 5;

  strikeTlm[6] = accX.bytes[3];
  strikeTlm[7] = accX.bytes[2];
  strikeTlm[8] = accX.bytes[1];
  strikeTlm[9] = accX.bytes[0];

  strikeTlm[10] = accY.bytes[3];
  strikeTlm[11] = accY.bytes[2];
  strikeTlm[12] = accY.bytes[1];
  strikeTlm[13] = accY.bytes[0];

  strikeTlm[14] = accZ.bytes[3];
  strikeTlm[15] = accZ.bytes[2];
  strikeTlm[16] = accZ.bytes[1];
  strikeTlm[17] = accZ.bytes[0];

  strikeTlm[18] = gyroX.bytes[3];
  strikeTlm[19] = gyroX.bytes[2];
  strikeTlm[20] = gyroX.bytes[1];
  strikeTlm[21] = gyroX.bytes[0];

  strikeTlm[22] = gyroY.bytes[3];
  strikeTlm[23] = gyroY.bytes[2];
  strikeTlm[24] = gyroY.bytes[1];
  strikeTlm[25] = gyroY.bytes[0];

  strikeTlm[26] = gyroZ.bytes[3];
  strikeTlm[27] = gyroZ.bytes[2];
  strikeTlm[28] = gyroZ.bytes[1];
  strikeTlm[29] = gyroZ.bytes[0];

  strikeTlm[30] = angleX.bytes[3];
  strikeTlm[31] = angleX.bytes[2];
  strikeTlm[32] = angleX.bytes[1];
  strikeTlm[33] = angleX.bytes[0];

  strikeTlm[34] = angleY.bytes[3];
  strikeTlm[35] = angleY.bytes[2];
  strikeTlm[36] = angleY.bytes[1];
  strikeTlm[37] = angleY.bytes[0];

  strikeTlm[38] = angleZ.bytes[3];
  strikeTlm[39] = angleZ.bytes[2];
  strikeTlm[40] = angleZ.bytes[1];
  strikeTlm[41] = angleZ.bytes[0];

  strikeTlm[42] = pressure.bytes[3];
  strikeTlm[43] = pressure.bytes[2];
  strikeTlm[44] = pressure.bytes[1];
  strikeTlm[45] = pressure.bytes[0];

  strikeTlm[46] = alttitude.bytes[3];
  strikeTlm[47] = alttitude.bytes[2];
  strikeTlm[48] = alttitude.bytes[1];
  strikeTlm[49] = alttitude.bytes[0];

  strikeTlm[50] = velocity.bytes[3];
  strikeTlm[51] = velocity.bytes[2];
  strikeTlm[52] = velocity.bytes[1];
  strikeTlm[53] = velocity.bytes[0];
//
//  strikeTlm[54] = longitude.bytes[3];
//  strikeTlm[55] = longitude.bytes[2];
//  strikeTlm[56] = longitude.bytes[1];
//  strikeTlm[57] = longitude.bytes[0];
//
//  strikeTlm[58] = latitude.bytes[3];
//  strikeTlm[59] = latitude.bytes[2];
//  strikeTlm[60] = latitude.bytes[1];
//  strikeTlm[61] = latitude.bytes[0];
  /////

  /////
}

void telemetryOutputSerial(void)
{
  for (int i = 0; i < tlm_length; i++)
  {
    Serial.write(strikeTlm[i]);
  }
}

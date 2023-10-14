//This field is for interpret date which received from telemetry
//There are 12 data

//initial global variable data
float acceX;
float acceY;
float acceZ;

float gyroX;
float gyroY;
float gyroZ;

float yaw;
float pitch;
float roll;

float pressure;
float alttitude;
float velocity;

float longitude;
float latitude;
int tlm_length = 65;

float special;

//function for process data
void processSerialData()
{ 
  int data;
  boolean dataReady;
  while (myPort.available() > 0)
  {
    data = myPort.read();
    dataReady = addData((byte)data);
    if(dataReady)
    {
    processTlmData();
    }
  }
}

boolean addData(byte nextChar)
{ 
  if (correctHeaderFlag == 1)
  {
    tlmBuffer[currentIndex] = nextChar;
    currentIndex++;
    
    if (currentIndex == tlm_length)
    {
      currentIndex = 0;
      correctHeaderFlag = 0;
      return true;
    }
  }
  
  if (nextChar == 'H' && correctHeaderFlag == 0)
  {
    tlmBuffer[currentIndex] = nextChar;
    correctHeaderFlag = 1;
    currentIndex++;
  }
  return false;
}

void processTlmData()
{
  int intbit = 0;
  
  //accelerometer
  intbit = (tlmBuffer[6] << 24) | ((tlmBuffer[7] & 0xff) << 16) | ((tlmBuffer[8] & 0xff) << 8) | (tlmBuffer[9] & 0xff);
  acceX = Float.intBitsToFloat(intbit);

  intbit = (tlmBuffer[10] << 24) | ((tlmBuffer[11] & 0xff) << 16) | ((tlmBuffer[12] & 0xff) << 8) | (tlmBuffer[13] & 0xff);
  acceY = Float.intBitsToFloat(intbit);

  intbit = (tlmBuffer[14] << 24) | ((tlmBuffer[15] & 0xff) << 16) | ((tlmBuffer[16] & 0xff) << 8) | (tlmBuffer[17] & 0xff);
  acceZ = Float.intBitsToFloat(intbit);

  // gyroscope
  intbit = (tlmBuffer[18] << 24) | ((tlmBuffer[19] & 0xff) << 16) | ((tlmBuffer[20] & 0xff) << 8) | (tlmBuffer[21] & 0xff);
  gyroX = Float.intBitsToFloat(intbit);

  intbit = (tlmBuffer[22] << 24) | ((tlmBuffer[23] & 0xff) << 16) | ((tlmBuffer[24] & 0xff) << 8) | (tlmBuffer[25] & 0xff);
  gyroY = Float.intBitsToFloat(intbit);

  intbit = (tlmBuffer[26] << 24) | ((tlmBuffer[27] & 0xff) << 16) | ((tlmBuffer[28] & 0xff) << 8) | (tlmBuffer[29] & 0xff);
  gyroZ = Float.intBitsToFloat(intbit);
  
   // angular
  intbit = (tlmBuffer[30] << 24) | ((tlmBuffer[31] & 0xff) << 16) | ((tlmBuffer[32] & 0xff) << 8) | (tlmBuffer[33] & 0xff);
  yaw = Float.intBitsToFloat(intbit);

  intbit = (tlmBuffer[34] << 24) | ((tlmBuffer[35] & 0xff) << 16) | ((tlmBuffer[36] & 0xff) << 8) | (tlmBuffer[37] & 0xff);
  pitch = Float.intBitsToFloat(intbit);

  intbit = (tlmBuffer[38] << 24) | ((tlmBuffer[39] & 0xff) << 16) | ((tlmBuffer[40] & 0xff) << 8) | (tlmBuffer[41] & 0xff);
  roll = Float.intBitsToFloat(intbit);
  
  //Pressure
  intbit = (tlmBuffer[42] << 24) | ((tlmBuffer[43] & 0xff) << 16) | ((tlmBuffer[44] & 0xff) << 8) | (tlmBuffer[45] & 0xff);
  pressure = Float.intBitsToFloat(intbit);
  
  //Alttitude
  intbit = (tlmBuffer[46] << 24) | ((tlmBuffer[47] & 0xff) << 16) | ((tlmBuffer[48] & 0xff) << 8) | (tlmBuffer[49] & 0xff);
  alttitude = Float.intBitsToFloat(intbit);
  
  //Temperature
  intbit = (tlmBuffer[50] << 24) | ((tlmBuffer[51] & 0xff) << 16) | ((tlmBuffer[52] & 0xff) << 8) | (tlmBuffer[53] & 0xff);
  velocity = Float.intBitsToFloat(intbit);
  
  ////longitude
  //intbit = (tlmBuffer[54] << 24) | ((tlmBuffer[55] & 0xff) << 16) | ((tlmBuffer[56] & 0xff) << 8) | (tlmBuffer[57] & 0xff);
  //longitude = Float.intBitsToFloat(intbit);
  
  ////latitude
  //intbit = (tlmBuffer[58] << 24) | ((tlmBuffer[59] & 0xff) << 16) | ((tlmBuffer[60] & 0xff) << 8) | (tlmBuffer[61] & 0xff);
  //latitude = Float.intBitsToFloat(intbit);
  
  ////special
  //intbit = (tlmBuffer[62] << 24) | ((tlmBuffer[63] & 0xff) << 16) | ((tlmBuffer[64] & 0xff) << 8) | (tlmBuffer[65] & 0xff);
  //special = Float.intBitsToFloat(intbit);
  
  // enable tlm update flag
  tlmUpdateFlag = true;
}
    

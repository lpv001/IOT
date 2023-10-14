#include "./cmd.h"

byte cmdBuffer[10];
int cmdCounter;
void processSerialData (void)
{
  int data;
  bool dataReady;
  while (Serial.available()>0)
  {
    data = Serial.read();
    dataReady = addData((char)data);
    if (dataReady)
    processData();
  }
}
bool addData (char nextChar)
{
  static uint8_t currentIndex =0;
  static uint8_t correctDatflag = 0;
  static uint8_t flag = 0;

  if(correctDatflag == 1)
{
  cmdBuffer[currentIndex] = nextChar;
  currentIndex++;

  if(currentIndex = 2)
  {
    currentIndex = 0;
    flag = 0;
    correctDatflag = 0;
    return true;
  }
}
if (nextChar == 'C' && flag == 0)
{ 
  cmdBuffer[currentIndex] = nextChar;
  currentIndex++;
  correctDatflag = 1;
  flag =1;
}
  return false;
}

int processData()
 {
  cmdCounter++;
  if(cmdBuffer[1] == 0x01)
  {
    value1 = 0;
  }
    if(cmdBuffer[1] == 0x04)
  {
    value1 = 1;
  }
  else if (cmdBuffer[1] == 0x02)
  {
    period = 500;
  }
  else if (cmdBuffer[1] == 0x03)
  {
    period = 20;
  }
 
 }
 


  

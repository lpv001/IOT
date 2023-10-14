import processing.serial.*;
Serial myPort;

char HEADER = 'H';

short LF = 10;

short portIndex;

int numReadings = 10;  
int readingCounter = 0;
Table table;
int currentIndex;
int flag;
int correctHeaderFlag;
int time;
int BMPOn;
int BMPOff;
int val;


byte[] tlmBuffer = new byte[128];
int value;
boolean tlmUpdateFlag = false;
int wait = 20;


PImage strike;

void setup() {
  //size(900, 500);
  size(2880, 1800);
  strike = loadImage("strike.jpg");

  surface.setTitle("STRIKE");
  surface.setResizable(true);
  String port = "/dev/cu.usbmodem14101";
  myPort = new Serial(this, port, 115200);
  guiInit();
  time = millis();

  table = new Table();
  table.addColumn("id");
  table.addColumn("AccX");
  table.addColumn("AccY");
  table.addColumn("AccZ");
  table.addColumn("GyroX");
  table.addColumn("GyroY");
  table.addColumn("GyroZ");
  table.addColumn("Yaw");
  table.addColumn("Pitch");
  table.addColumn("Roll");
  table.addColumn("Pressure");
  table.addColumn("Temperature");
  table.addColumn("Alttitude");

  myPort.bufferUntil('\n');
}

void draw() {

  background(0);
  image(strike, 0, 0);
  strike.resize(0, 250);
  //if (myPort.available() > 0)
  //{ 
  //  val = myPort.readStringUntil('\n');

  //  if (val!=null) {
  //    val = trim(val);
  //    val1 = float(val);
  //  }
   TableRow newRow = table.addRow();
  newRow.setInt("id", table.getRowCount() - 1);
  newRow.setFloat("AccX", acceX);
  newRow.setFloat("AccY", acceY);
  newRow.setFloat("AccZ", acceZ);
  newRow.setFloat("GyroX", gyroX);
  newRow.setFloat("GyroY", gyroY);
  newRow.setFloat("GyroZ", gyroZ);
  newRow.setFloat("Yaw", yaw);
  newRow.setFloat("Pitch", pitch);
  newRow.setFloat("Roll", roll);
  newRow.setFloat("Pressure", pressure);
  newRow.setFloat("Alttitude", alttitude);
  newRow.setFloat("Temperature", velocity);
  

  readingCounter++;

  if (readingCounter % numReadings ==0)
  {
    saveTable(table, "data/Avionics.csv");
  }

  layout();
  processSerialData();


  currentTime.setText(nf(hour(), 2)+":"+nf(minute(), 2)+":"+nf(second(), 2));
  currentDate.setText(nf(day(), 2)+"-"+nf(month(), 2)+"-"+year());

  if (millis() - time > wait)
  {
    time = millis();
    
    // push data from function received to text
    acceXText.setText(nf(acceX, 0, 2) + "\n" + nf(acceY, 0, 2) + "\n" + nf(acceZ, 0, 2) + "\n"); 
    gyroText.setText(nf(gyroX, 0, 2) + "\n" + nf(gyroY, 0, 2) + "\n" + nf(gyroZ, 0, 2) + "\n");
    anguText.setText(nf(yaw, 0, 2) + "\n" + nf(pitch, 0, 2) + "\n" + nf(roll, 0, 2) + "\n");
    pressureText.setText(nf(pressure, 0, 2) + " Pascal");
    alttitudeText.setText(nf(alttitude, 0, 2) + " H");
    velocityText.setText(nf(velocity, 0, 2) + "m/s");
    longitudeText.setText(nf(longitude, 0, 2));
    latitudeText.setText(nf(latitude, 0, 2));

    // push data from function received to chart
    acceChart.push("acceVX", acceX);
    acceChart.push("acceVY", acceY);
    acceChart.push("acceVZ", acceZ);

    gyroChart.push("gyroVX", gyroX);
    gyroChart.push("gyroVY", gyroY);
    gyroChart.push("gyroVZ", gyroZ);

    anguChart.push("yaw", yaw);
    anguChart.push("pitch", pitch);
    anguChart.push("roll", roll);

    //PressureChart.push("pressure", pressure);
    //AlttiChart.push("alttitude", alttitude);
  }

  if (Value1==1) BMPOn();
  else if (Value1 ==0) BMPOff();
}

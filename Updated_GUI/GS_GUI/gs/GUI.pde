//This field is for draw and design gui

//library controlP5
import controlP5.*;

ControlP5 cp5;

Chart myChart, PressureChart, AlttiChart, acceChart, gyroChart, anguChart;

Textlabel acceXText;

Textlabel gyroText;

Textlabel anguText;

Textlabel currentTime;

Textlabel currentDate;

Textlabel pressureText;

Textlabel alttitudeText;

Textlabel velocityText;

Textlabel longitudeText;

Textlabel latitudeText;


int knobValue = 100;
int Value1;
int Power1;
Knob myKnobB;

int x = 20; //20
int y = 140; //140

// tab width

int tabWidth = 250; //250

int tabHeight = 40; //40
int boxHeight = 100; //100

int offSet = 20; //20

// color
int b= 80; //40


void layout() 
{
  
  stroke(b+20);
  fill(b);
  
  //Line under the title
  fill(#00004a);
  rect(x + 400, y - 80, tabWidth + 230 , tabHeight - 50);
  stroke(0);

  //Local time
  fill(b-20);
  rect(x + 280 , y - 35, tabWidth + 100 , tabHeight + 20);
  //fill(b);
  //rect(x + 280, y - 100, tabWidth, boxHeight - 50);
  
  
  //Date
  fill(b-20);
  rect(x + 650 , y - 35, tabWidth + 200 , tabHeight + 20);
  
  //Operator
  fill(b-20);
  rect(x + 315 , y + 40, tabWidth + 500 , tabHeight + 20);
  
  //CMD
  fill(b-20);
  rect(x - 20, y + 130 , tabWidth + 60 , tabHeight);
  fill(b);
  rect(x - 20, y + 170, tabWidth + 60, boxHeight + 370);
  
  // BPM180
  fill(b-20);
  rect(x + 260, y + 130 , tabWidth + 130, tabHeight);
  fill(b);
  rect(x + 260, y + 170, tabWidth + 130, boxHeight + 370);
  
  // MPU6050
  fill(b-20);
  rect(x + 630, y + 130 , tabWidth + 210, tabHeight);
  fill(b);
  rect(x + 630, y + 170, tabWidth + 210, boxHeight + 370);


  // RawData
  fill(b-20);
  rect(x + 1080, y + 130 , tabWidth + 40 , tabHeight);
  fill(b);
  rect(x + 1080, y + 170, tabWidth + 40, boxHeight + 370);

}

void guiInit()
{
  
  PFont fontt;
  PFont fontlocaltime;
  PFont fonttitle;
  PFont fontBMP;
  PFont fontMPU;
  PFont fontnormal;
  PFont fonttlm;
  
  
  cp5 = new ControlP5(this);

  fontt = createFont("Georgia", 14); //14

  fontlocaltime = createFont("Georgia", 24); //24

  fonttitle = createFont("Georgia", 38); //18

  fontBMP = createFont("Georgia", 17); //11

  fontMPU = createFont("Georgia", 18); //11
  
  fontnormal = createFont("Georgia", 18); //11
  
  fonttlm = createFont("Georgia", 11); //11

  cp5 = new ControlP5(this);
  
   // text label
  //cp5.addTextlabel("Strike")
  //  .setBroadcast(false)
  //  .setText("Strike")
  //  .setPosition(x + 800, y -300)
  //  .setFont(font1)
  //  .setBroadcast(true);
  
 // Strike title
  cp5.addTextlabel("Strike")
    .setBroadcast(false)
    .setText("STRIKE: Small Solid Rocket")
    .setPosition(x + 400, y - 120)
    .setFont(fonttitle)
    .setBroadcast(true);
    
    
    
//Local Time
 cp5.addTextlabel("LocalTime")
    .setBroadcast(false)
    .setText("Time:")
    .setPosition(x + 320 , y - 20)
    .setFont(fontlocaltime)
    .setBroadcast(true);

 currentTime = cp5.addTextlabel("currentTime")
    .setBroadcast(false)
    .setText("00:00:00")
    .setPosition(x + 400 , y - 20)
    .setFont(fontlocaltime)
    .setBroadcast(true);
  
//Date
 cp5.addTextlabel("Date")
    .setBroadcast(false)
    .setText("Date:")
    .setPosition(x + 700 , y - 20)
    .setFont(fontlocaltime)
    .setBroadcast(true);

 currentDate = cp5.addTextlabel("currentDate")
    .setBroadcast(false)
    .setText("01/01/2021")
    .setPosition(x + 800 , y - 20)
    .setFont(fontlocaltime)
    .setBroadcast(true);
    
    
//Operator Label
 cp5.addTextlabel("Operator Label")
    .setBroadcast(false)
    .setText("Operation:")
    .setPosition(x + 350 , y + 55)
    .setFont(fontlocaltime)
    .setBroadcast(true);
    
 // CMD label
  cp5.addTextlabel("CMD Label")
    .setBroadcast(false)
    .setText("CMD")
    .setPosition(x + 80, y + 140)
    .setFont(fontBMP)
    .setBroadcast(true);
    
   
//BMP180 label
  cp5.addTextlabel("BMP180 Label")
    .setBroadcast(false)
    .setText("BMP180")
    .setPosition(x + 410, y + 140)
    .setFont(fontBMP)
    .setBroadcast(true);


//MPU6050 label
  cp5.addTextlabel("MPU6050 Label")
    .setBroadcast(false)
    .setText("MPU6050")
    .setPosition(x + 810, y + 140)
    .setFont(fontMPU)
    .setBroadcast(true);
    
//RawData label
  cp5.addTextlabel("RawData Label")
    .setBroadcast(false)
    .setText("Raw Data")
    .setPosition(x + 1180, y + 140)
    .setFont(fontMPU)
    .setBroadcast(true);
    

 
//Knob Value
myKnobB = cp5.addKnob("Power")
               .setRange(0,5)
               .setValue(2.5)
               .setFont(fontMPU)
               .setPosition(x + 1130, y - 120)
               .setRadius(100)
               .setNumberOfTickMarks(2)
               .setTickMarkLength(2)
               .snapToTickMarks(true)
               .setColorForeground(color(255))
               .setColorBackground(color(#00004a))
               .setColorActive(color(255,255,0))
               .setDragDirection(Knob.HORIZONTAL)
               ;
 
 

//GRAPH

 
//Pressure Graph 
PressureChart = cp5.addChart("Pressure Value")
    .setPosition(x + 280, y + 200)
    .setSize(tabWidth + 80 , boxHeight + 50)
    .setRange(0, 1023)
    .setView(Chart.LINE) // use Chart.LINE, Chart.PIE, Chart.AREA, Chart.BAR_CENTERED
    .setStrokeWeight(1.5)
    .setColorCaptionLabel(color(255))
    .setFont(fontMPU);
    ;
 
PressureChart.getColor().setBackground(#00004a);
  
//Alttitude Graph
AlttiChart = cp5.addChart("Alttitude Value")
    .setPosition(x + 280, y + 390)
    .setSize(tabWidth + 80 , boxHeight + 50)
    .setRange(0, 1023)
    .setView(Chart.LINE) // use Chart.LINE, Chart.PIE, Chart.AREA, Chart.BAR_CENTERED
    .setStrokeWeight(1.5)
    .setColorCaptionLabel(color(255))
    .setFont(fontMPU);
    ;
 
AlttiChart.getColor().setBackground(#00004a);
  
//Accelaremeter Graph
acceChart = cp5.addChart("Accelerometer Value")
    .setPosition(x + 650, y + 200)
    .setSize(tabWidth + 160 , boxHeight)
    .setRange(0, 100)
    .setView(Chart.LINE) // use Chart.LINE, Chart.PIE, Chart.AREA, Chart.BAR_CENTERED
    .setStrokeWeight(1.5)
    .setColorCaptionLabel(color(255))
    .setFont(fontMPU);
    ;
 
acceChart.getColor().setBackground(#00004a);  
  
  
//Gyrometer Graph
gyroChart = cp5.addChart("Gyroscope Value")
    .setPosition(x + 650, y + 325)
    .setSize(tabWidth + 160 , boxHeight)
    .setRange(0, 100)
    .setView(Chart.LINE) // use Chart.LINE, Chart.PIE, Chart.AREA, Chart.BAR_CENTERED
    .setStrokeWeight(1.5)
    .setColorCaptionLabel(color(255))
    .setFont(fontMPU);
    ;
 
gyroChart.getColor().setBackground(#00004a); 


//Angular Graph
anguChart = cp5.addChart("Angular Value")
    .setPosition(x + 650, y + 450)
    .setSize(tabWidth + 160 , boxHeight)
    .setRange(0, 100)
    .setView(Chart.LINE) // use Chart.LINE, Chart.PIE, Chart.AREA, Chart.BAR_CENTERED
    .setStrokeWeight(1.5)
    .setColorCaptionLabel(color(255))
    .setFont(fontMPU);
    ;
 
anguChart.getColor().setBackground(#00004a); 
  
  
  
  
//Raw Data  

//Pressure
cp5.addTextlabel("Pressure")
    .setBroadcast(false)
    .setText("Pressure :                               ")
    .setPosition(x + 1100, y + 200)
    .setFont(fontnormal)
    .setBroadcast(true);

  pressureText = cp5.addTextlabel("PressureData")
    .setBroadcast(false)
    .setText("0 Pascal")
    .setPosition(x + 1240, y + 200)
    .setFont(fontnormal)
    .setBroadcast(true);
    
    
//Alttitude
cp5.addTextlabel("Alttitude")
    .setBroadcast(false)
    .setText("Alttitude :                               ")
    .setPosition(x + 1100, y + 240)
    .setFont(fontnormal)
    .setBroadcast(true);

  alttitudeText = cp5.addTextlabel("AlttitudeData")
    .setBroadcast(false)
    .setText("0 H")
    .setPosition(x + 1240, y + 240)
    .setFont(fontnormal)
    .setBroadcast(true);
    
    
//Accelerometer
cp5.addTextlabel("Accelerometer")
    .setBroadcast(false)
    .setText("Accelerometer :                               ")
    .setPosition(x + 1100, y + 280)
    .setFont(fontnormal)
    .setBroadcast(true);

  acceXText = cp5.addTextlabel("AccelerometerData")
    .setBroadcast(false)
    .setText("0x, 0y, 0z")
    .setPosition(x + 1240, y + 280)
    .setFont(fontnormal)
    .setBroadcast(true);

//Gyroscope
cp5.addTextlabel("Gyroscope")
    .setBroadcast(false)
    .setText("Gyroscope :                               ")
    .setPosition(x + 1100, y + 360)
    .setFont(fontnormal)
    .setBroadcast(true);

  gyroText = cp5.addTextlabel("GyroscopeData")
    .setBroadcast(false)
    .setText("0x, 0y, 0z")
    .setPosition(x + 1240, y + 360)
    .setFont(fontnormal)
    .setBroadcast(true);
    
    
//Angular
cp5.addTextlabel("Angular")
    .setBroadcast(false)
    .setText("Angular :                               ")
    .setPosition(x + 1100, y + 440)
    .setFont(fontnormal)
    .setBroadcast(true);

  anguText = cp5.addTextlabel("AngularData")
    .setBroadcast(false)
    .setText("0x, 0y, 0z")
    .setPosition(x + 1240, y + 440)
    .setFont(fontnormal)
    .setBroadcast(true);


//Temperature
cp5.addTextlabel("velocity")
    .setBroadcast(false)
    .setText("velocity :                               ")
    .setPosition(x + 1100, y + 520)
    .setFont(fontnormal)
    .setBroadcast(true);

  velocityText = cp5.addTextlabel("velocityData")
    .setBroadcast(false)
    .setText("celcius")
    .setPosition(x + 1240, y + 520)
    .setFont(fontnormal)
    .setBroadcast(true);
    
//Longitude
cp5.addTextlabel("Longitude")
    .setBroadcast(false)
    .setText("Longitude : ")
    .setPosition(x + 1100, y + 540)
    .setFont(fontnormal)
    .setBroadcast(true);

  longitudeText = cp5.addTextlabel("LongitudeData")
    .setBroadcast(false)
    .setText("")
    .setPosition(x + 1240, y + 540)
    .setFont(fontnormal)
    .setBroadcast(true);
    
//Latitude
cp5.addTextlabel("Latitude")
    .setBroadcast(false)
    .setText("Latitude : ")
    .setPosition(x + 1100, y + 560)
    .setFont(fontnormal)
    .setBroadcast(true);

  latitudeText = cp5.addTextlabel("LatitudeData")
    .setBroadcast(false)
    .setText("")
    .setPosition(x + 1240, y + 560)
    .setFont(fontnormal)
    .setBroadcast(true);
 
//Buttons
    
// Acce and Gyro tlm control bottons
cp5.addButton("tlm500")
    .setBroadcast(false)
    .setValue(0)
    .setPosition(x  , y + 200)
    .setSize(100, 30)
    .setBroadcast(true)
    .setFont(fonttlm)
    ;

cp5.addButton("tlm20")
    .setBroadcast(false)
    .setValue(0)
    .setPosition(x + 125, y + 200)
    .setSize(100, 30)
    .setBroadcast(true)
    .setFont(fonttlm)
    ;
        

//BMP180 buttom
  cp5.addButton("BMPOn")
    .setBroadcast(false)
    .setValue(0)
    .setPosition(x  , y + 320)
    .setSize(120, 40)
    .setFont(fontMPU)
    .setBroadcast(true)
    ;
   cp5.addButton("BMPOff")
    .setBroadcast(false)
    .setValue(0)
    .setPosition(x + 130, y + 320)
    .setSize(120, 40)
    .setFont(fontMPU)
    .setBroadcast(true)
    ;

//MPU6050 buttom
  cp5.addButton("MPUOn")
    .setBroadcast(false)
    .setValue(0)
    .setPosition(x , y + 260)
    .setSize(120, 40)
    .setFont(fontMPU)
    .setBroadcast(true)
    ;
   cp5.addButton("MPUOff")
    .setBroadcast(false)
    .setValue(0)
    .setPosition(x + 130, y + 260)
    .setSize(120, 40)
    .setFont(fontMPU)
    .setBroadcast(true)
    ;


//PowerON buttom
 cp5.addButton("PowerON")
    .setBroadcast(false)
    .setValue(0)
    .setPosition(x + 570 , y + 40)
    .setSize(200, 60)
    .setFont(fontMPU)
    .setBroadcast(true)
    ;

    
//PowerOFF buttom
  cp5.addButton("PowerOFF")
    .setBroadcast(false)
    .setValue(0)
    .setPosition(x + 800 , y + 40)
    .setSize(200, 60)
    .setFont(fontMPU)
    .setBroadcast(true)
    ;
  
//Get data

//Acce
acceChart.addDataSet("acceVX")
    .setData("acceVX", new float[200])
    .setColors("acceVX", color(255, 0, 0));

  acceChart.addDataSet("acceVY")
    .setData("acceVY", new float[200])
    .setColors("acceVY", color(0, 255, 0));

  acceChart.addDataSet("acceVZ")
    .setData("acceVZ", new float[200])
    .setColors("acceVZ", color(255));

  
//Gyro 
gyroChart.addDataSet("gyroVX")
    .setData("gyroVX", new float[200 ])
    .setColors("gyroVX", color(255, 0, 0));

  gyroChart.addDataSet("gyroVY")
    .setData("gyroVY", new float[200])
    .setColors("gyroVY", color(0, 255, 0));

  gyroChart.addDataSet("gyroVZ")
    .setData("gyroVZ", new float[200])
    .setColors("gyroVZ", color(255));
    

// Angular
anguChart.addDataSet("yaw")
    .setData("yaw", new float[200])
    .setColors("yaw", color(255, 0, 0));

  anguChart.addDataSet("pitch")
    .setData("pitch", new float[200])
    .setColors("pitch", color(0, 255, 0));

  anguChart.addDataSet("roll")
    .setData("roll", new float[200])
    .setColors("roll", color(255));
    
//Pressure
PressureChart.addDataSet("pressure")
    .setData("pressure", new float[200])
    .setColors("pressure", color(0,0,255));
    
//Alttitude
AlttiChart.addDataSet("alttitude")
    .setData("alttitude", new float[200])
    .setColors("alttitude", color(0,255,0));

}
    
  

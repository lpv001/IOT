#include <Wire.h>
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "PozzVenh";
const char* password =  "012286451";
int counter = 0;

void setup() {
  // Start the I2C Bus as Master
  Wire.begin(); 
  Serial.begin(115200);
  delay(4000);
  pinMode(0x02,OUTPUT);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network");
}
void loop() { 
  
  if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
 
    HTTPClient http;
    
    http.begin("https://smartfarm.kasegro.com/api/instructions"); //Specify the URL
    int httpCode = http.GET();                                        //Make the request
    
    if (httpCode > 0) { //Check for the returning code
        digitalWrite(0x02,HIGH);
        String payload = http.getString();
        //Serial.println(httpCode);
        //Serial.println(payload);

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------

if(payload == "0"){
  
  Wire.beginTransmission(9);
  Wire.write(0);
  Wire.endTransmission();
}
else if(payload == "1"){
  Wire.beginTransmission(9);
  Wire.write(1);
  Wire.endTransmission();
}
else if(payload == "2"){
  Wire.beginTransmission(9);
  Wire.write(2);
  Wire.endTransmission();
}
else if(payload == "3"){
  Wire.beginTransmission(9);
  Wire.write(3);
  Wire.endTransmission();
}
else if(payload == "4"){
  Wire.beginTransmission(9);
  Wire.write(4);
  Wire.endTransmission();
}
else if(payload == "5"){
  Wire.beginTransmission(9);
  Wire.write(5);
  Wire.endTransmission();
}
else if(payload == "6"){
  Wire.beginTransmission(9);
  Wire.write(6);
  Wire.endTransmission();
}
else if(payload == "7"){
  Wire.beginTransmission(9);
  Wire.write(7);
  Wire.endTransmission();
}
else if(payload == "8"){
  Wire.beginTransmission(9);
  Wire.write(8);
  Wire.endTransmission();
}
else if(payload == "9"){
  Wire.beginTransmission(9);
  Wire.write(9);
  Wire.endTransmission();
}
else{}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
 
        
      }
 
    else {
      digitalWrite(0x02,LOW);
      Wire.beginTransmission(9);
      Wire.write(0);
      Wire.endTransmission();
      //Serial.println("Error on HTTP request");
      delay(60000);
      ESP.restart();
    }
   
    http.end(); //Free the resources
  }else{
    ESP.restart();
    //Serial.println("Connecting to wifi");
    delay(10000);
  }
  counter++;
  if(counter == 3600){
    ESP.restart();
    counter =0 ;
  }
  
}

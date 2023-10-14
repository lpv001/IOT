#include "DHT.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>


#define DHTPIN D2    
#define DHTTYPE DHT11  

DHT dht(DHTPIN, DHTTYPE);


const char* ssid = "Kasegro";
const char* password = "myfarm@123";

//Your Domain name with URL path or IP address with path
const char* serverName = "https://smartfarm.kasegro.com/api/sensors/storeData";


unsigned long lastTime = 0;
unsigned long timerDelay = 60000;

int initial_state = 0;

float humidity = 0;
float temperature = 0;

void setup() {
 
  Serial.begin(115200);
  dht.begin();

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    ++initial_state;
    Serial.println("Connecting to WiFi..");
    if ( initial_state == 15 ){
      initial_state = 0;
      break;
    }
  }

  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);
  Serial.println("Connected to the WiFi network");
 
}

void loop() {


  delay(2000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (!isnan(h) || !isnan(t)) {
    humidity = h;
    temperature = t;
  }

 
  if ((millis() - lastTime) > timerDelay) {


    if(WiFi.status()== WL_CONNECTED){
      WiFiClientSecure client;
      client.setInsecure();
      HTTPClient http;

      String urlString = "mac_address=8&type1=1&val1=" + String(humidity) + "&type2=2&val2=" + String(temperature);
     
      http.begin(client, serverName);
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");

      int httpResponseCode = http.POST(urlString);
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
       
     
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
     
}

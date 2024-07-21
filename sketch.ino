#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Wokwi-GUEST";
const char* pass = "";

const char* serverUrl = "https://s-m.com.sa/r.html"; 
unsigned const long interval = 2000;
unsigned long zero = 0;
const int red = 25; 
const int green = 12; 
const int white = 14; 
const int purple = 27; 
const int yellow = 33; 

void setup() {
  Serial.begin(115200);
  pinMode(red, OUTPUT); 
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.println(".");
  }
  Serial.println("WiFi Connected!");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (millis() - zero > interval) {
    HTTPClient http;
    http.begin(serverUrl);
    int httpResponseCode = http.GET();
    if (httpResponseCode > 0) {
      String payload = http.getString();
      Serial.print("Server Response: ");
      Serial.println(payload);

      if (payload == "forward") {
        digitalWrite(red, HIGH);
        Serial.println("forward LED Turned ON");
      } else if (payload == "backward") {
        digitalWrite(green, HIGH); 
        Serial.println("backward LED Turned ON");
      }else if (payload == "stop") {
        digitalWrite(white, HIGH); 
        Serial.println("stop LED Turned ON");
      }else if (payload == "left") {
        digitalWrite(purple, HIGH); 
        Serial.println("left LED Turned ON");
      } else if (payload == "right") {
        digitalWrite(yellow, HIGH); 
        Serial.println("right LED Turned ON");
      } else {
        Serial.println("Invalid command");
      }
    } else {
      Serial.print("Error fetching data: ");
      Serial.println(httpResponseCode);
    }
    zero = millis();
  }
}
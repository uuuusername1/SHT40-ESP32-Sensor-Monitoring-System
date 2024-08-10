#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <Adafruit_SHT4x.h>

const char* ssid = "SSID";        // Replace with your Wi-Fi SSID
const char* password = "PASS"; // Replace with your Wi-Fi password
const char* serverName = "IP OR FQND"; // Replace with your FQDN

Adafruit_SHT4x sht4 = Adafruit_SHT4x();

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  if (!sht4.begin()) {
    Serial.println("Couldn't find SHT4x sensor!");
    while (1) delay(1);
  }
  Serial.println("SHT4x Found!");
}

void loop() {
  sensors_event_t humidity, temp;

  if (sht4.getEvent(&humidity, &temp)) {
    Serial.print("Temperature: ");
    Serial.print(temp.temperature);
    Serial.println(" °C");
  
    Serial.print("Humidity: ");
    Serial.print(humidity.relative_humidity);
    Serial.println(" %");

    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      http.begin(serverName);

      String postData = "temperature=" + String(temp.temperature) + "&humidity=" + String(humidity.relative_humidity);
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");

      int httpResponseCode = http.POST(postData);

      if (httpResponseCode > 0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
      } else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      
      http.end();
    } else {
      Serial.println("WiFi Disconnected");
    }
  } else {
    Serial.println("Error reading sensor data");
  }

  delay(2000);  // Wait 2 seconds between readings
}

#include <TinyGPS++.h>
#include <WiFi.h>
#include <HTTPClient.h>

// WiFi credentials
const char* ssid = "WALPAD8G_V2";
const char* password = "Emon1877530";

// ThingSpeak
const char* server = "http://api.thingspeak.com/update";
const char* apiKey = "RHG706OEJZJ2LHU6";

// GPS pins
#define GPS_TX_PIN 27
#define GPS_RX_PIN 26

TinyGPSPlus gps;

void setup() {
  Serial.begin(115200);
  Serial.println("🚀 ESP32 + NEO-6M GPS + ThingSpeak");

  Serial1.begin(9600, SERIAL_8N1, GPS_TX_PIN, GPS_RX_PIN);

  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n✅ WiFi Connected!");
}

void loop() {
  // Read GPS data
  while (Serial1.available() > 0) {
    gps.encode(Serial1.read());
  }

  static unsigned long lastSend = 0;

  if (millis() - lastSend >= 5000) {
    lastSend = millis();

    Serial.println("🛰️ Getting GPS Data…");

    if (gps.location.isValid()) {
      float lat = gps.location.lat();
      float lon = gps.location.lng();
      float alt = gps.altitude.isValid() ? gps.altitude.meters() : 0.0;
      int sats = gps.satellites.isValid() ? gps.satellites.value() : 0;
      float hdop = gps.hdop.isValid() ? gps.hdop.value() : 0.0;
      float spd = gps.speed.isValid() ? gps.speed.kmph() : 0.0;

      Serial.printf("Lat: %.6f, Lon: %.6f, Alt: %.2f m, Sats: %d, HDOP: %.2f, Speed: %.2f km/h\n",
        lat, lon, alt, sats, hdop, spd);

      // Build ThingSpeak URL
      String url = String(server) + "?api_key=" + apiKey +
                   "&field1=" + String(lat, 6) +
                   "&field2=" + String(lon, 6) +
                   "&field3=" + String(spd, 2) +
                   "&field4=" + String(sats) +
                   "&field5=" + String(alt, 2) +
                   "&field6=" + String(hdop, 2);

      HTTPClient http;
      http.begin(url);
      int httpCode = http.GET();
      if (httpCode > 0) {
        Serial.print("✅ ThingSpeak HTTP Response: ");
        Serial.println(httpCode);
      } else {
        Serial.print("❌ HTTP Error: ");
        Serial.println(http.errorToString(httpCode));
      }
      http.end();
    } else {
      Serial.println("⚠️ GPS fix not yet acquired.");
    }

    Serial.println("-----------------------------------\n");
  }
}

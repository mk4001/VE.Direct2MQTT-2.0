/*
  © MK 15 Jan 2024
  Write Victron Energy MPPT fields to MQTT
  based on ESP32 Wroom using Uses VeDirectFrameHandler library
*/

void connectToWiFi() {
  Serial.print("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("connected");
}

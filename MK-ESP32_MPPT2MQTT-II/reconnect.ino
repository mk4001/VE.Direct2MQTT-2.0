/*
  © MK 15 Jan 2024
  Write Victron Energy MPPT fields to MQTT
  based on ESP32 Wroom using Uses VeDirectFrameHandler library
*/

void reconnect() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT...");
    if (client.connect("ESP32-WROOM")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" retrying in 5 seconds");
      delay(5000);
    }
  }
}

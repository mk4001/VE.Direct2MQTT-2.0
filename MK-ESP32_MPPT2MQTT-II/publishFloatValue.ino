/*
  © MK 15 Jan 2024
  Write Victron Energy MPPT fields to MQTT
  based on ESP32 Wroom using Uses VeDirectFrameHandler library
*/

void publishFloatValue(const char* topic, float value) {
  char message[20];
  snprintf(message, sizeof(message), "%.2f", value);
  client.publish(topic, message);
}

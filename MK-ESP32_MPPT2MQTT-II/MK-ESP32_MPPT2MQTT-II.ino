/*
  © MK 15 Jan 2024
  Write Victron Energy MPPT fields to MQTT
  based on ESP32 Wroom using Uses VeDirectFrameHandler library
*/

/*************************************************************************************
 ReadVeDirectFrameHandler

 Uses VeDirectFrameHandler library

 This example and library tested with NodeMCU 1.0 using Software Serial.
 If using with a platform containing 2 harware UART's, use those, not SoftwareSerial.
 Tested with Victron BMV712.

 VEDirect Device:
   pin 1 - gnd
   pin 2 - RX
   pin 3 - TX
   pin 4 - power

 History:
   2020.05.05 - 0.3 - initial release

**************************************************************************************/

#include "Arduino.h"
#include "VeDirectFrameHandler.h"

#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "WLAN 7490-2.4GHz";
const char* password = "06431928919070006302";
const char* mqttServer = "rpi.fritz.box";
const int mqttPort = 1883;
//const char* mqttUser = "NOME_UTENTE_MQTT";
//const char* mqttPassword = "PASSWORD_MQTT";

long rec_count = 0;

WiFiClient espClient;
PubSubClient client(espClient);

VeDirectFrameHandler myve;

//Define ESP32 HW Serial port #2 PIN 16(RX) - 17(TX - not used)
#define SERIAL_PORT Serial2


void setup() {
  Serial.begin(115200);  // output serial port

  SERIAL_PORT.begin(19200);  // input serial port (VE device)
  SERIAL_PORT.flush();
  Serial.println("DEBUG-setup");

  // log helper
  myve.setErrorHandler(&LogHelper);
  // hex protocol callback
  myve.addHexCallback(&HexCallback, (void*)42);

  connectToWiFi();

  client.setServer(mqttServer, mqttPort);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  ReadVEData();
  EverySecond();
}
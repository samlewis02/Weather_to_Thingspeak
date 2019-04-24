/*

GET data from the BME280 environmental sensor
using I2C interface. Get local weather from
openweathermap.org. Send data to Thingspeak

Written: APR 24 2019

Connecting the BME280 Sensor:
Sensor              ->  Board
-----------------------------
Vin (Voltage In)    ->  3.3V
Gnd (Ground)        ->  Gnd
SDA (Serial Data)   ->  D2 on NodeMCU
SCK (Serial Clock)  ->  D1 on NodeMCU


 */
#include "DebugMacros.h"
#include <Arduino.h>
#include <BME280I2C.h>
#include <ESP8266WiFi.h>
#include <SPI.h>
#include <ThingSpeak.h>
#include <Wire.h>
#include "SendDataThingSpeak.h"
#include "getBME280Data.h"
#include "getWeather.h"
#include "parseJson.h"

const char *ssid = "*********";
const char *pass = "*********";
unsigned long myChNumber = 123456;
const char *myWriteAPIKey = "SDAFBRESAGNJR";

WiFiClient client;

int *xtern;  // array for external readings
int *intern; // array for internal readings

BME280I2C bme;

void setup() {
  Serial.begin(115200);

  Wire.begin();

  while (!bme.begin()) {
    DPRINTLN("Could not find BME280 sensor!");
    delay(1000);
  }

  switch (bme.chipModel()) {
  case BME280::ChipModel_BME280:
    DPRINTLN("Found BME280 sensor! Success.");
    break;
  case BME280::ChipModel_BMP280:
    DPRINTLN("Found BMP280 sensor! No Humidity available.");
    break;
  default:
    DPRINTLN("Found UNKNOWN sensor! Error!");
  }
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    yield();
    delay(500);
    Serial.print(".");
  }
  DPRINTLN("Connected");
  ThingSpeak.begin(client);
}

//////////////////////////////////////////////////////////////////
void loop() {
  getBME280Data();
  xtern = parse_json(getWeather());
  intern = getBME280Data();
  SendDataThingSpeak(xtern, intern, myChNumber, myWriteAPIKey);
  delay(30000);
}

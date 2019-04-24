#include <Arduino.h>
#include <ArduinoJson.h>
#include "DebugMacros.h"
#include "parseJson.h"
int * parse_json(String r) {
    static int sensor[3];
  // Allocate JsonBuffer
  // Use arduinojson.org/assistant to compute the capacity.
  const size_t capacity = JSON_OBJECT_SIZE(3) + JSON_ARRAY_SIZE(2) + 60;
  // DynamicJsonBuffer jsonBuffer(capacity);
  DynamicJsonDocument jdoc(2000); // V6 edit

  // Parse JSON object
  // JsonObject& root = jsonBuffer.parseObject(r);
  DeserializationError d_error = deserializeJson(jdoc, r); // V6 edit

  if (d_error) {
    DPRINTLN(F("Parsing failed!"));
    return 0;
  } else {
    float wt = jdoc["main"]["temp"];
    int wtemp = (int)(round(wt));
    sensor[0] = wtemp;
    float wh = jdoc["main"]["humidity"];
    int whum = (int)(round(wh));
    sensor[1] = whum;
    float wp = jdoc["main"]["pressure"];
    int wpres = (int)(round(wp));
    sensor[2] = wpres;

    DPRINT("Temperature = "); DPRINTLN(wtemp);
    DPRINT("Humidity = "); DPRINTLN(whum);
    DPRINT("Pressure = "); DPRINTLN(wpres);
    return sensor;
  }
}

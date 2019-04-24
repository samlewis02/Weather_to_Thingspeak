#include "DebugMacros.h"
#include <Arduino.h>
#include <ESP8266HTTPClient.h>
String getWeather() {
  String response;
  HTTPClient http;
  const String city1 = "Kaohsiung,TW";
  const String city2 = "Northampton,GB";
  String myPlace = city1;
  DPRINT("[HTTP] begin...\n");
  // configure url
  String url = "http://api.openweathermap.org/data/2.5/weather?q=" + myPlace +
               "&units=metric&APPID=67e5ccb428706c8f055d13402093c432";
  // http.begin("http://api.openweathermap.org/data/2.5/weather?q=Kaohsiung,TW&units=metric&APPID=67e5ccb428706c8f055d13402093c432");
  // //HTTP
  http.begin(url);
  DPRINT("[HTTP] GET...\n");
  // start connection and send HTTP header
  int httpCode = http.GET();

  // httpCode will be negative on error
  if (httpCode > 0) {
    // HTTP header has been send and Server response header has been handled
    DPRINT("[HTTP] GET... code: ");
    DPRINTLN(httpCode);

    // file found at server
    if (httpCode == HTTP_CODE_OK) {
      response = http.getString();
      DPRINTLN(response);
    }
  } else {
    DPRINT("[HTTP] GET... failed, error: ");
    DPRINTLN(http.errorToString(httpCode).c_str());
    response = "";
  }

  http.end();
  return response;
}

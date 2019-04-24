#include "DebugMacros.h"

#include "getBME280Data.h"

int *getBME280Data(void) {
  static int readings[3];
  float temp(NAN), hum(NAN), pres(NAN);

  BME280::TempUnit tempUnit(BME280::TempUnit_Celsius);
  BME280::PresUnit presUnit(BME280::PresUnit_bar);

  bme.read(pres, temp, hum, tempUnit, presUnit);

  int ltemp = (int)(round(temp));
  readings[0] = ltemp;
  int lhum = (int)(round(hum));
  readings[1] = lhum;
  int lpres = (int)(round(pres * 1000));
  readings[2] = lpres;
  DPRINT("Temp = ");
  DPRINTLN(ltemp);
  DPRINT("Hum = ");
  DPRINTLN(lhum);
  DPRINT("Pres = ");
  DPRINTLN(lpres);
  return readings;
}

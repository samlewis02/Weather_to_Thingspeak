#ifndef _GETBME_H
#define _GETBME_H
#include <BME280I2C.h>
extern BME280I2C bme;
int * getBME280Data (void);
#endif

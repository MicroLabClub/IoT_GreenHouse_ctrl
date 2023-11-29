#include "Arduino.h"
#include <Adafruit_BMP085.h>

/***************************************************
  This is an example for the BMP085 Barometric Pressure & Temp Sensor

  Designed specifically to work with the Adafruit BMP085 Breakout
  ----> https://www.adafruit.com/products/391

  These pressure and temperature sensors use I2C to communicate, 2 pins
  are required to interface
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ****************************************************/

// Connect VCC of the BMP085 sensor to 3.3V (NOT 5.0V!)
// Connect GND to Ground
// Connect SCL to i2c clock - on '168/'328 Arduino Uno/Duemilanove/etc thats Analog 5
// Connect SDA to i2c data - on '168/'328 Arduino Uno/Duemilanove/etc thats Analog 4
// EOC is not used, it signifies an end of conversion
// XCLR is a reset pin, also not used here

Adafruit_BMP085 bmp;

float ed_bmp_temperature = 0;
float ed_bmp_pressure = 0;

int ed_bmp_sensor_error = 0;

float ed_bmp_GetTemperature(void)
{
  return ed_bmp_temperature;
}

float ed_bmp_GetPressure(void)
{
  return ed_bmp_pressure;
}

int ed_bmp_GetSensorError(void)
{
  return ed_bmp_sensor_error;
}

void ed_bmp_setup()
{
  Serial.begin(9600);
  //  Initialize device.
  if (!bmp.begin())
  {
    Serial.println("ED BMP: Could not find a valid BMP085 sensor, check wiring!");
    ed_bmp_sensor_error = 1;
  }
}

void ed_bmp_loop()
{

  if (ed_bmp_sensor_error == 0)
  {
    ed_bmp_temperature = bmp.readTemperature();
    Serial.print("ED BMP: Temperature = ");
    Serial.print(ed_bmp_temperature);
    Serial.println(" *C");

    ed_bmp_pressure = bmp.readPressure();
    Serial.print("ED BMP: Pressure = ");
    Serial.print(ed_bmp_pressure);
    Serial.println(" Pa");

    Serial.println();
  }
}
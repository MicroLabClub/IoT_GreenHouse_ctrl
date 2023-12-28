#include "Arduino.h"
#include <Wire.h>
#include <BH1750.h>

BH1750 lightMeter(0x23);

float ed_bh1750_luminozity = 0;
int ed_bh1750_luminozity_error = 0;

float ed_bh1750_get_luminozity(void)
{
  return ed_bh1750_luminozity;
}

int ed_bh1750_get_luminozity_error(void)
{
  return ed_bh1750_luminozity_error;
}

void ed_bh1750_setup()
{

    // Initialize the I2C bus (BH1750 library doesn't do this automatically)
    Wire.begin();
    // On esp8266 you can select SCL and SDA pins using Wire.begin(D4, D3);

    /*

      BH1750 has six different measurement modes. They are divided in two groups;
      continuous and one-time measurements. In continuous mode, sensor
      continuously measures lightness value. In one-time mode the sensor makes
      only one measurement and then goes into Power Down mode.

      Each mode, has three different precisions:

        - Low Resolution Mode - (4 lx precision, 16ms measurement time)
        - High Resolution Mode - (1 lx precision, 120ms measurement time)
        - High Resolution Mode 2 - (0.5 lx precision, 120ms measurement time)

      By default, the library uses Continuous High Resolution Mode, but you can
      set any other mode, by passing it to BH1750.begin() or BH1750.configure()
      functions.

      [!] Remember, if you use One-Time mode, your sensor will go to Power Down
      mode each time, when it completes a measurement and you've read it.

      Full mode list:

        BH1750_CONTINUOUS_LOW_RES_MODE
        BH1750_CONTINUOUS_HIGH_RES_MODE (default)
        BH1750_CONTINUOUS_HIGH_RES_MODE_2

        BH1750_ONE_TIME_LOW_RES_MODE
        BH1750_ONE_TIME_HIGH_RES_MODE
        BH1750_ONE_TIME_HIGH_RES_MODE_2

    */

    // begin returns a boolean that can be used to detect setup problems.
    if (lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE))
    {
        // Serial.println(F("BH1750 Advanced begin"));
        ed_bh1750_luminozity_error = 0;
    }
    else
    {
        // Serial.println(F("Error initialising BH1750"));
        ed_bh1750_luminozity_error = 1;
    }
}

void ed_bh1750_loop()
{
  if (lightMeter.measurementReady()) {
    float lux = lightMeter.readLightLevel();
    ed_bh1750_luminozity = lux;
    // Serial.print("Light: ");
    // Serial.print(lux);
    // Serial.println(" lx");
  }
}

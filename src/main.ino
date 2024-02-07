#include <SPI.h>
#include "NHB_AD7794.h"


#define AD7794_CS 4		



AD7794 adc(AD7794_CS, 4000000, 2.50);

void setup()
{
  adc.begin();

  adc.setUpdateRate(470);   

  adc.setBipolar(0, true);
  adc.setGain(0, 128);
  adc.setEnabled(0, true);

  adc.setMode(AD7794_OpMode_Continuous);
  
}

void loop()
{     
    double reading;     

    uint32_t count = 0;
    static uint32_t lastCount = 0;
    uint32_t stop = millis() + 1000;

    while (millis() < stop)
    {
        reading = adc.read(0);

        Serial.print(voltsToEngUnits(reading, 5),DEC);
        Serial.print('\t');
        Serial.print(lastCount);
        Serial.println("Hz");

        ++count;
    }

    lastCount = count;

}

float voltsToEngUnits(float volts,float scaleFactor){
  const float vEx = 2.5;

  float mVpV = (volts * 1000) / vEx;
  return mVpV * scaleFactor;
}
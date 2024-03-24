// Tested and compiled with no errors
// measuring AC current using ACS712 current sensor with ESP32 Microcontroller
// The ACS712 works with high voltage AC so be careful !
// source - /www.circuitschools.com
 
#include <LiquidCrystal_I2C.h>

const int sensorIn = 34;      // pin where the OUT pin from sensor is connected on Arduino
int mVperAmp = 100;           // this the 5A version of the ACS712 -use 100 for 20A Module and 66 for 30A Module
int Watt = 0;
double Voltage = 0;
double VRMS = 0;
double AmpsRMS = 0;
 

void setup() {
  Serial.begin (115200); 
  Serial.println ("ACS712 current sensor"); 
  // Initialize the LCD connected 
  delay(1000);
}
 
void loop() {

  
  //Voltage = getVPP();
  // VRMS = (Voltage/2.0) *0.707;   //root 2 is 0.707
  // AmpsRMS = ((VRMS * 1000)/mVperAmp)-0.3; //0.3 is the error I got for my sensor
 
  // Serial.print(AmpsRMS);
  // Serial.print(" Amps RMS  ---  ");
  // Watt = (AmpsRMS*240/1.2);
  // note: 1.2 is my own empirically established calibration factor
  // as the voltage measured at D34 depends on the length of the OUT-to-D34 wire
  // 240 is the main AC power voltage – this parameter changes locally
  // Serial.print(Watt);
  // Serial.println(" Watts");

   String a = String(analogRead(34));
   String b = String(analogRead(35));
   Serial.print(a);
   Serial.print(",");
   Serial.print(b);
   Serial.println (""); 

  delay (1);
}
 
// ***** function calls ******
float getVPP()
{
  float result;
  int readValue;                // value read from the sensor
  int maxValue = 0;             // store max value here
  int minValue = 4096;          // store min value here ESP32 ADC resolution
  
   uint32_t start_time = millis();
   while((millis()-start_time) < 2) //sample for 1 Sec
   {
       readValue = analogRead(sensorIn);
       // see if you have a new maxValue
       if (readValue > maxValue) 
       {
           /*record the maximum sensor value*/
           maxValue = readValue;
       }
       if (readValue < minValue) 
       {
           /*record the minimum sensor value*/
           minValue = readValue;
       }
   }
  
   // Subtract min from max
   result = ((maxValue - minValue) * 3.3)/4096.0; //ESP32 ADC resolution 4096  
   return result;
 }
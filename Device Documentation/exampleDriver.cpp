
#include "M5607.hpp"
#include "BNO055.hpp"
#include "ADXL375.hpp"

#include <Wire.h>


m5607 altimeter;
bno055 imu055;
adxl375 accelerometer;



void setup()
{    


    Wire.begin();

    //altimeter.OnStart();
    //imu055.OnStart();
    accelerometer.OnStart();

    Serial.begin(115200);
    Serial.println("Orientation Sensor Test"); Serial.println("");

}

void loop() 
{ 
    // D2=m5607_i2c_cmd_adc(CMD_ADC_D2+CMD_ADC_4096); // read D2
    // D1=m5607_i2c_cmd_adc(CMD_ADC_D1+CMD_ADC_4096); // read D1
    // calcualte 1st order pressure and temperature (MS5607 1st order algorithm) 

    altimeter.OnUpdate();
    //imu055.OnUpdate();
    //accelerometer.OnUpdate();    




}
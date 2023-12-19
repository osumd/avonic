
#include "M5607.hpp"
#include "BNO055.hpp"
#include "ADXL375.hpp"
#include "XTSG04.hpp"
// #include "BNO0085.hpp"
#include "MAX31856.hpp"
#include "FPGM.hpp"
#include <Wire.h>


m5607 altimeter;
bno055 imu055;
// bno0085 imu085;
adxl375 accelerometer;
xtsg04  file;
max1856 thermo;
fpgm    gps;

void setup()
{    

    
    Wire.begin();
    Serial.begin(9600);

    Serial.println("Orientation Sensor Test"); Serial.println("");

    //altimeter.OnStart();
    //accelerometer.OnStart();
    // imu085.OnStart();
    //imu055.OnStart();

    //thermo.OnStart();

    gps.OnStart();
    
    

    // imu085.InitateReadings(&file);
    //altimeter.InitateReadings(&file);
    //thermo.InitateReadings(&file);
    




}

void loop() 
{ 
    // D2=m5607_i2c_cmd_adc(CMD_ADC_D2+CMD_ADC_4096); // read D2
    // D1=m5607_i2c_cmd_adc(CMD_ADC_D1+CMD_ADC_4096); // read D1
    // calcualte 1st order pressure and temperature (MS5607 1st order algorithm) 
    // imu085.ReportReadings(&file);
    //altimeter.ReportReadings(&file);
    //imu055.ReportReadings(&file);
    //thermo.ReportReadings(&file);
    //accelerometer.ReportReadings(&file);
    //Serial.println("Loop");
    gps.OnUpdate();
    //imu055.OnUpdate();
    //accelerometer.OnUpdate();    
    //gps.OnUpdate();


}
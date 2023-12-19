#ifndef  M5607_H
#define  M5607_H

#include "MS5607I2C.hpp"
#include "MS5607I2Ccommands.hpp"

struct m5607
{
  unsigned long D1; // ADC value of the pressure conversion 
  unsigned long D2; // ADC value of the temperature conversion 
  unsigned int C[8]; // calibration coefficients 
  double P; // compensated pressure value 
  double T; // compensated temperature value 
  double dT; // difference between actual and measured temperature 
  double OFF; // offset at actual temperature 
  double SENS; // sensitivity at actual temperature 
  int i; 
  unsigned char n_crc; // crc value of the prom 
  unsigned int ps_pin = 19; // pin on teensy device connected to PS

  void OnStart()
  {
      pinMode(ps_pin, OUTPUT); //set to PS pin on device to high for i2c
      digitalWrite(ps_pin, HIGH); 

      D1=0; 
      D2=0;

      m5607_i2c_cmd_reset(); // reset IC 
      for (i=0;i<8;i++){ C[i]=m5607_i2c_cmd_prom(i);} // read coefficients 
      n_crc=m5607_i2c_crc4(C); // calculate the CRC
  }

  void OnUpdate()
  {
    D2=m5607_i2c_cmd_adc(CMD_ADC_D2+CMD_ADC_4096); // read D2
    D1=m5607_i2c_cmd_adc(CMD_ADC_D1+CMD_ADC_4096); // read D1
    // calcualte 1st order pressure and temperature (MS5607 1st order algorithm) 
    dT=D2-C[5]*pow(2,8); 
    OFF=C[2]*pow(2,17)+dT*C[4]/pow(2,6); 
    SENS=C[1]*pow(2,16)+dT*C[3]/pow(2,7); 
    
    T=(2000+(dT*C[6])/pow(2,23))/100; 
    P=(((D1*SENS)/pow(2,21)-OFF)/pow(2,15))/100; 
  }

};


#endif
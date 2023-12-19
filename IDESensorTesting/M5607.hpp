#ifndef  M5607_H
#define  M5607_H

#include "MS5607I2C.hpp"
#include "MS5607I2Ccommands.hpp"
#include "xtsg04.hpp"
#include <Wire.h>

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

  void OnStart()
  {
      D1=0; 
      D2=0;

      m5607_i2c_cmd_reset(); // reset IC 
      Serial.print("Command Prom: ");

      for (i=0;i<8;i++){ C[i]=m5607_i2c_cmd_prom(i); Serial.print("C"); Serial.print(i); Serial.print(" "); Serial.print(C[i]); } // read coefficients 
      n_crc=m5607_i2c_crc4(C); // calculate the CRC
      Serial.println();
      Serial.print("n_crc: ");
      Serial.print(n_crc);
      Serial.println();
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

    Serial.print("D1: ");
    Serial.print(D1);
    Serial.print(" ,");
    Serial.print("D2: ");
    Serial.print(D2);
    Serial.print(" ,");
    Serial.print("dT: ");
    Serial.print(dT);
    Serial.print(" ,");
    Serial.print("T: ");
    Serial.print(T);
    Serial.print(" ,");
    Serial.print("P: ");
    Serial.print(P);
    Serial.println("--");


  }

  void InitateReadings(xtsg04* file)
  {

    file->WriteToFile("D1,D2,T,P","m5607readings.txt");
    file->WriteToFile("\n","m5607readings.txt");
    


  }

  void ReportReadings(xtsg04* file)
  { 
    D2=m5607_i2c_cmd_adc(CMD_ADC_D2+CMD_ADC_4096); // read D2
    D1=m5607_i2c_cmd_adc(CMD_ADC_D1+CMD_ADC_4096); // read D1
    // calcualte 1st order pressure and temperature (MS5607 1st order algorithm) 
    dT=D2-C[5]*pow(2,8); 
    OFF=C[2]*pow(2,17)+dT*C[4]/pow(2,6); 
    SENS=C[1]*pow(2,16)+dT*C[3]/pow(2,7); 
    
    T=(2000+(dT*C[6])/pow(2,23))/100; 
    P=(((D1*SENS)/pow(2,21)-OFF)/pow(2,15))/100; 

    Serial.print("D1: ");
    Serial.print(D1);
    Serial.print(" ,");
    Serial.print("D2: ");
    Serial.print(D2);
    Serial.print(" ,");
    Serial.print("dT: ");
    Serial.print(dT);
    Serial.print(" ,");
    Serial.print("T: ");
    Serial.print(T);
    Serial.print(" ,");
    Serial.print("P: ");
    Serial.print(P);
    Serial.println("--");
    
    file->WriteToFile(D1,"m5607readings.txt");
    file->WriteToFile(",","m5607readings.txt");
    file->WriteToFile(D2,"m5607readings.txt");
    file->WriteToFile(",","m5607readings.txt");
    file->WriteToFile(T,"m5607readings.txt");
    file->WriteToFile(",","m5607readings.txt");
    file->WriteToFile(P,"m5607readings.txt");
    file->WriteToFile("\n","m5607readings.txt");
  }

  

};


#endif
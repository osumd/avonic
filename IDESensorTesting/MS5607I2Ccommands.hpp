#ifndef MS5607_COMMANDS_H
#define MS5607_COMMANDS_H

#include "MS5607I2C.hpp"

unsigned long m5607_i2c_cmd_adc(char cmd); 
unsigned int m5607_i2c_cmd_prom(char coef_num); 
unsigned char m5607_i2c_crc4(unsigned int n_prom[]); 


#endif
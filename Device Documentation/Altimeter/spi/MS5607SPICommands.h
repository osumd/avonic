#ifndef MS5607_SPI_COMMANDS_H
#define MS5607_SPI_COMMANDS_H
#include "MS5607SPI.h"


unsigned long ms5607_spi_cmd_adc(char cmd); 
unsigned int ms5607_spi_cmd_prom(char coef_num); 
unsigned char ms5607_spi_crc4(unsigned int n_prom[]); 


#endif
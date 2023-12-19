#ifndef MS5607_SPI_H
#define MS5607_SPI_H

#define TRUE 1 
#define FALSE 0 

#define MS5607_CS_PIN 10 // Control switch on the current board setup.
#define MS5607_SCK 13 // SCK SPI Clock Output
#define MS5607_MOSI 11 // Message Out Sock In
#define MS5607_MISO 12 // Message In Sock Out

#define CMD_RESET 0x1E // ADC reset command 
#define CMD_ADC_READ 0x00 // ADC read command 
#define CMD_ADC_CONV 0x40 // ADC conversion command 
#define CMD_ADC_D1 0x00 // ADC D1 conversion 
#define CMD_ADC_D2 0x10 // ADC D2 conversion 
#define CMD_ADC_256 0x00 // ADC OSR=256 
#define CMD_ADC_512 0x02 // ADC OSR=512 
#define CMD_ADC_1024 0x04 // ADC OSR=1024 
#define CMD_ADC_2048 0x06 // ADC OSR=2048 
#define CMD_ADC_4096 0x08 // ADC OSR=4096 
#define CMD_PROM_RD 0xA0 // Prom read command 

unsigned char ms5607_spi_send(char cmd);
void          ms5607_cs_low();
void          ms5607_cs_high();
void          ms5607_spi_cmd_reset(void); 

#endif

#include "MS5607SPI.h"
#include "MS5607SPICommands.h"

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

void setup(void)
{

    SPI.begin();
    ms5607_spi_cmd_reset();
    for(int i = 0; i < 8; i++)
    {
        C[i] = ms5607_spi_cmd_prom(i);
    }

}

void loop(void)
{
    D1=ms5607_spi_cmd_adc(CMD_ADC_D1+CMD_ADC_256); // read uncompensated pressure 
    D2=ms5607_spi_cmd_adc(CMD_ADC_D2+CMD_ADC_4096); // read uncompensated temperature 
    
    // calcualte 1st order pressure and temperature (MS5607 1st order algorithm) 
    dT=D2-C[5]*pow(2,8); 
    OFF=C[2]*pow(2,17)+dT*C[4]/pow(2,6); 
    SENS=C[1]*pow(2,16)+dT*C[3]/pow(2,7); 
    
    T=(2000+(dT*C[6])/pow(2,23))/100; 
    P=(((D1*SENS)/pow(2,21)-OFF)/pow(2,15))/100; 
    // place to use P, T, put them on LCD, send them trough RS232 interface... 
}

int main(void)
{

    while(1)
    {
        loop();
    }


}
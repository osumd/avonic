#include "MS5607SPI.h"

unsigned char ms5607_spi_send(char cmd)
{   
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
    unsigned char response = SPI.transfer(cmd);
    SPI.endTransaction();
    return response;
}

void          ms5607_cs_low()
{
    digitalWrite(MS5607_CS_PIN, LOW); // Select the SPI slave device if necessary
}
void          ms5607_cs_high()
{
    digitalWrite(MS5607_CS_PIN, HIGH);
}

void ms5607_spi_cmd_reset(void)
{
    ms5607_spi_send(ms5607_spi_cmd_reset);
}
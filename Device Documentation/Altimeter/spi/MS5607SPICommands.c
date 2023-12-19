#include "MS5607SPICommands.h"
//******************************************************** 
//! @brief preform adc conversion 
//! 
//! @return 24bit result 
//******************************************************** 
unsigned long ms5607_spi_cmd_adc(char cmd)
{
    unsigned int ret; 
    unsigned long temp=0; 

    ms5607_cs_low(); // pull CSB low
    ms5607_spi_send(CMD_ADC_CONV+cmd); // send conversion command 
    
    switch (cmd & 0x0f) // wait necessary conversion time 
    { 
        case CMD_ADC_256 : _delay_us(900); break; 
        case CMD_ADC_512 : _delay_ms(3); break; 
        case CMD_ADC_1024: _delay_ms(4); break; 
        case CMD_ADC_2048: _delay_ms(6); break; 
        case CMD_ADC_4096: _delay_ms(10); break; 
    } 
    ms5607_cs_high(); // pull CSB high to finish the conversion 
    ms5607_cs_low(); // pull CSB low to start new command
    ms5607_spi_send(CMD_ADC_READ); // send ADC read command
    ret=ms5607_spi_send(0x00); // send 0 to read 1st byte (MSB) 
    
    temp=65536*ret; 
    ret=spi_send(0x00); // send 0 to read 2nd byte 
    temp=temp+256*ret; 
    ret=spi_send(0x00); // send 0 to read 3rd byte (LSB) 
    
    temp=temp+ret; 

    ms5607_cs_high(); // pull CSB high to finish the read command 

    return temp;
} 
//******************************************************** 
//! @brief Read calibration coefficients 
//! 
//! @return coefficient 
//********************************************************
unsigned int ms5607_spi_cmd_prom(char coef_num)
{
    unsigned int ret; 
    unsigned int rC=0; 
    
    ms5607_cs_low(); // pull CSB low 
    ms5607_spi_send(CMD_PROM_RD+coef_num*2); // send PROM READ command 
    ret=ms5607_spi_send(0x00); // send 0 to read the MSB 
    rC=256*ret; 
    ret=ms5607_spi_send(0x00); // send 0 to read the LSB 
    rC=rC+ret; 
    ms5607_cs_high(); // pull CSB high 
    return rC;
} 
//******************************************************** 
//! @brief calculate the CRC code for details look into AN521 
//! 
//! @return crc code 
//********************************************************
unsigned char ms5607_spi_crc4(unsigned int n_prom[])
{
    int cnt; // simple counter 
    unsigned int n_rem; // crc reminder 
    unsigned int crc_read; // original value of the crc 
    unsigned char n_bit; 
    n_rem = 0x00; 
    crc_read=n_prom[7]; //save read CRC 
    n_prom[7]=(0xFF00 & (n_prom[7])); //CRC byte is replaced by 0 
    for (cnt = 0; cnt < 16; cnt++) // operation is performed on bytes 
    { // choose LSB or MSB 
        if (cnt%2==1) n_rem ^= (unsigned short) ((n_prom[cnt>>1]) & 0x00FF); 
        else n_rem ^= (unsigned short) (n_prom[cnt>>1]>>8); 
        for (n_bit = 8; n_bit > 0; n_bit--) 
        { 
            if (n_rem & (0x8000)) 
            { 
                n_rem = (n_rem << 1) ^ 0x3000;
            } 
            else 
            { 
                n_rem = (n_rem << 1); 
            } 
        } 
    } 
    n_rem= (0x000F & (n_rem >> 12)); // // final 4-bit reminder is CRC code 
    n_prom[7]=crc_read; // restore the crc_read to its original place 
    return (n_rem ^ 0x00); 

} 

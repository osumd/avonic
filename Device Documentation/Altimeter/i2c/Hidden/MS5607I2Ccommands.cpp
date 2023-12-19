#include "MS5607I2Ccommands.hpp"

//******************************************************** 
//! @brief preform adc conversion 
//! 
//! @return 24bit result 
//******************************************************** 
unsigned long m5607_i2c_cmd_adc(char cmd) 
{ 
    unsigned int ret; 
    unsigned long temp=0; 
    m5607_i2c_send(CMD_ADC_CONV+cmd); // send conversion command 
    switch (cmd & 0x0f) // wait necessary conversion time 
    { 
        // case CMD_ADC_256 : _delay_us(900); break; 
        // case CMD_ADC_512 : _delay_ms(3); break; 
        // case CMD_ADC_1024: _delay_ms(4); break; 
        // case CMD_ADC_2048: _delay_ms(6); break; 
        // case CMD_ADC_4096: _delay_ms(10); break; 
    } 

    m5607_i2c_send(CMD_ADC_READ); 
    ret = m5607_i2c_start(ADDR_R); // set device address and read mode 
    if ( ret ) 
    {//failed to issue start condition, possibly no device found 
        m5607_i2c_stop(); 
    } 
    else 
    {//issuing start condition ok, device accessible 
        ret = m5607_i2c_readAck(); // read MSB and acknowledge 
        temp=65536*ret; 
        ret = m5607_i2c_readAck(); // read byte and acknowledge 
        temp=temp+256*ret; 
        ret = m5607_i2c_readNak(); // read LSB and not acknowledge 
        temp=temp+ret; 
        m5607_i2c_stop(); // send stop condition 
    } return temp; 
} 
//******************************************************** 
//! @brief Read calibration coefficients 
//! 
//! @return coefficient 
//******************************************************** 
unsigned int m5607_i2c_cmd_prom(char coef_num) 
{ 
    unsigned int ret; 
    unsigned int rC=0; 

    m5607_i2c_send(CMD_PROM_RD+coef_num*2); // send PROM READ command 
    ret = m5607_i2c_start(ADDR_R); // set device address and read mode 
    if ( ret ) 
    {//failed to issue start condition, possibly no device found 
    m5607_i2c_stop(); 
    } 
    else 
    {//issuing start condition ok, device accessible 
    ret = m5607_i2c_readAck(); // read MSB and acknowledge 
    rC=256*ret; 
    ret = m5607_i2c_readNak(); // read LSB and not acknowledge 
    rC=rC+ret; 
    m5607_i2c_stop(); 
    } 
    return rC; 
} 
//******************************************************** 
//! @brief calculate the CRC code 
//! 
//! @return crc code 
//******************************************************** 
unsigned char m5607_i2c_crc4(unsigned int n_prom[]) 
{ 
    int cnt; // simple counter 
    unsigned int n_rem; // crc reminder 
    unsigned int crc_read; // original value of the crc 
    unsigned char n_bit; 
    n_rem = 0x00; 
    crc_read=n_prom[7]; //save read CRC 
    n_prom[7]=(0xFF00 & (n_prom[7])); //CRC byte is replaced by 0 
    for (cnt = 0; cnt < 16; cnt++) // operation is performed on bytes 
    {// choose LSB or MSB 
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
    n_rem= (0x000F & (n_rem >> 12)); // final 4-bit reminder is CRC code n_prom[7]=crc_read; // restore the crc_read to its original place 
    return (n_rem ^ 0x0); 
} 

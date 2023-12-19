#include "MS5607I2C.h"

//******************************************************** 
//! @brief send I2C start condition and the address byte 
//! 
//! @return 0 
//******************************************************** 
unsigned char m5607_i2c_start(unsigned char address)
{
    //device being the deviceAddress, that needs to be used in the other functions.
    Wire.beginTransmission(address); // send START condition and address
    unsigned char transmissionStatus = Wire.endTransmission(); // end transmission and get status

    if (transmissionStatus == 0 || transmissionStatus == 1) {
        return 0; // Success, device acknowledged
    } else {
        return 1; // Error, device did not acknowledge
    } 
} 

//******************************************************** 
//! @brief send I2C stop condition 
//! 
//! @return none 
//******************************************************** 
void m5607_i2c_stop(void)
{
    Wire.endTransmission();
} 

//******************************************************** 
//! @brief write data to wire. 
//! 
//! @return 0 If Success and 1 If Failure.
//********************************************************
unsigned char m5607_i2c_write(unsigned char data)
{
    Wire.write(data); // send data to the device
    unsigned char twst = Wire.endTransmission(); // end transmission and get status
    if (twst == 0) {
        return 0; // Success, data sent and acknowledged by the device
    } else {
        return 1; // Error, data not acknowledged by the device
    }
} 

//******************************************************** 
//! @brief read I2C byte with acknowledgment 
//! 
//! @return read byte 
//******************************************************** 
unsigned char m5607_i2c_readAck(void) 
{ 
    //This function is problematic and may cause system failure.

    Wire.requestFrom(deviceAddress, 1); // Request 1 byte from the device with ACK
    while (Wire.available() <= 0); // Wait until data is available
    unsigned char receivedData = Wire.read(); // Read the received byte
    return receivedData;
} 
//******************************************************** 
//! @brief read I2C byte without acknowledgment 
//! 
//! @return read byte 
//******************************************************** 
unsigned char m5607_i2c_readNak(void) 
{ 
    unsigned char receivedData = Wire.read(false); // Read a byte without sending ACK
    return receivedData; 
} 
//******************************************************** 
//! @brief send command using I2C hardware interface 
//!//! @return none 
//******************************************************** 
void m5607_i2c_send(char cmd) 
{ 
    unsigned char ret; 
    ret = i2c_start(ADDR_W); // set device address and write mode 
    if ( ret ) 
    {//failed to issue start condition, possibly no device found */ 
        i2c_stop(); 
    } 
    else 
    {
        // issuing start condition ok, device accessible 
        ret=i2c_write(cmd); 
        i2c_stop(); 
    } 
} 
//******************************************************** 
//! @brief send reset sequence 
//! 
//! @return none 
//******************************************************** 
void m5607_i2c_cmd_reset(void) 
{ 
    i2c_send(CMD_RESET); // send reset sequence 
    _delay_ms(3); // wait for the reset sequence timing 
} 


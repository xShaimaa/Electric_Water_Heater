#include "EEPROM.h"

void EEPROM_write(unsigned char _data){
    I2C1_Start();              // issue I2C start signal
    I2C1_Wr(0xA2);             // send byte via I2C  (device address + W)
    I2C1_Wr(0xff);             // send byte (address of EEPROM location)
    I2C1_Wr(_data);            // send data (data to be written)
    I2C1_Stop();               // issue I2C stop signal
}

unsigned char EEPROM_read(){
    unsigned short _data;
    I2C1_Start();              // issue I2C start signal
    I2C1_Wr(0xA2);             // send byte via I2C  (device address + W)
    I2C1_Wr(0xff);             // send byte (data address)
    I2C1_Start();              // issue I2C signal repeated start
    I2C1_Wr(0xA3);             // send byte (device address + R)
    _data = I2C1_Rd(0);        // Read the data (NO acknowledge)
    I2C1_Stop();               // issue I2C stop signal
    return _data;  
}
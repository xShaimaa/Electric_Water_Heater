#ifndef EEPROM_H_
#define EEPROM_H_

//functions prototype

/*fuction that is used to write the data 
 *in a patrticular address in the external EEPROM*/
void EEPROM_write(unsigned char _data);

/*a function that returns the stored data 
 *in a particular addres in the external EEPROM*/
unsigned char EEPROM_read();

#endif
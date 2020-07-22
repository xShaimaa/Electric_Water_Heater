#include "Temp_Sensor_Display.h"
#include "TMR1.h"
#include "normal_mode.h"
#include "setting_mode.h"
#include "EEPROM.h"
#include "main.h"

//variables

unsigned char measured_temp;                                //variable to store the surrent temp of the system
unsigned char set_temp = 40;                                //variable to storethe temp. set by the user
mode_t mode = normal_mode;                                        //data type holding the system mode state
power_t power = power_off;                                        //data type holding the system power state
unsigned char _data;
unsigned char EEPROM_flag;

//ISR
void Interrupt(){
        //timer1 survice routine, it's set every 10ms
        if (TMR1IF_bit){                                                
            if (mode == normal_mode){
            button_normal ();
            measured_temp = Temp_samples();
            control_temp(set_temp);
            heating_led ();
            Sensor_Display (measured_temp);
            }
            else if (mode == setting_mode){
                button_setting ();
                seg_blink();
            }
                //clearing the timer1 flag bit
            TMR1IF_bit = 0;                                   
            //relaoding the timer required value for 10 ms delay
            TMR1H = 0xB1;
            TMR1L = 0xE0;
        }
        //IRQ
        if (INTF_bit){
            if (power == power_off){
                T1CON |= (1<<0);
                power = power_on;
             }
            else if (power == power_on){
                power = power_off;
                        PORTB =0;
                PORTC =0;
                PORTD =0;
                T1CON &= ~(1<<0);
            }
                //clearing the external interrupt flag bit
            INTF_bit = 0;
        }
}

void main (){
    I2C1_Init(100000);                                         // initialize I2C communication
    ADC_begin();                                                        // initializin the ADC module
    TMR1_Init();                                                        // initializin the timer1 module
    normal_init();                                                        // initializin the normal mode for the system
    Seg_Init();                                                                // initializin the 7-seg
    T1CON &= ~(1<<0);                                                // turinig timer1 off
    
    _data = EEPROM_read();
    if( (_data >=35) && (_data <= 75) ){
        set_temp = _data;
    }
    else {
         set_temp = 60;
    }
    while(1){
              if (EEPROM_flag){
                 EEPROM_flag = 0;
                 EEPROM_write(set_temp);
              }
    }
}
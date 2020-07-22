#include "normal_mode.h"
#include "main.h"

//defining variables
extern mode_t mode;                                                //vaiable to store the current working state mode
extern unsigned char measured_temp ;        //variable to store the current temp. in the system
unsigned char led_counter;                                //counter used to blink the heating element led every 1sec
unsigned char normal_break;                                //counter used to 
temp_control_flag_t temp_flag ;                        //flag to control the heater and cooler

void normal_init(){
        //setting the heater as output 
        Heater_TRIS = 0;
    Heater_PORT = 0;
        //setting the cooler as output
    Cooler_TRIS = 0;
    Cooler_PORT = 0;
        //setting the heating element led as output 
    heating_element_TRIS = 0;
    heating_element_PORT = 0;
        //setting the up and down buttons and power button as input
    dwn_button_TRIS = 1;
    dwn_button_PORT = 0;
    up_button_TRIS = 1;
    up_button_PORT = 0;
    power_button_TRIS = 1;
        //enabling the interrupt
    INTCON |= (1<<4);
    INTCON |= (1<<6);
    INTF_bit = 0;
}

void button_normal(){
        normal_break ++;
        if (normal_break == BUTTON_CHECK_TIME){                //after 100 ms, check if a button is pressed
            normal_break = 0;                        //setting up the counter
        if ((up_button_PORT ==0) || (dwn_button_PORT ==0)){
                mode = setting_mode;        //if any button is presed, switch to setting mode
            //turning the heater and the cooler along with the heating element
                        Heater_PORT = 0;
            Cooler_PORT = 0;
            heating_element_PORT = 0;
        }
    }
}

void control_temp(int temp){
        //turn the heater on till the temp. reaches the requred temp. +5
    if ( measured_temp < (temp - 5) ){
            Heater_PORT = 1;
        Cooler_PORT = 0;
        temp_flag = heater_on ;
    }

        //turn the cooler on till the temp. reaches the requred temp. -5
    else if ( measured_temp > (temp + 5) ){
        Heater_PORT = 0;
        Cooler_PORT = 1;
        temp_flag = cooler_on ;
    }
}

void heating_led (){
        //blink the heating element while the heater is on
    if ( temp_flag == heater_on){
        led_counter ++;
        if (led_counter == LED_BLINK){
                heating_element_PORT ^= 1;
            led_counter = 0;
        }
     }
    //turning the heating element on while the cooler is on 
    else if ( temp_flag == cooler_on){
            heating_element_PORT = 1;
    }
}
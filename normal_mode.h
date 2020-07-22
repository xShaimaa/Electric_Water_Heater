#ifndef NORMAL_MODE_H
#define NORMAL_MODE_H

//heater and cooler configurations
#define Heater_TRIS TRISC.RC5
#define Heater_PORT PORTC.RC5

#define Cooler_TRIS TRISC.RC2
#define Cooler_PORT PORTC.RC2

#define heating_element_TRIS TRISB.RB7
#define heating_element_PORT PORTB.RB7

#define power_button_TRIS TRISB.RB0
#define power_button_PORT PORTB.RB0

//counters
#define LED_BLINK 100
#define BUTTON_CHECK_TIME 10


typedef enum{
        cooler_on,
        heater_on
}temp_control_flag_t ;

/*function used to intialize the prephirals used in the normal mode,
 * which re the heater and the cooler, heating element,
 * up and down buttons and the power button and enaling the interrupt*/
void normal_init();

/*function the checks the state of the up and down buttons
 *every 100ms using a counter, if any of them is pressed
 *the sysytem switches to the setting mode*/
void button_normal ();

/*function to check the system's tempreture,
 *turnning the heater or the cooler on and oscillate 
 *around the requred temp. */
void control_temp(int temp);

/*function that controls the heating element led,
 *the led is to be on while the cooler is on
 *and blinking while the heater is on*/
void heating_led ();

#endif
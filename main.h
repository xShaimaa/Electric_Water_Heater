#ifndef MAIN_H_
#define MAIN_H_

//up button configuration registers
#define up_button_TRIS TRISB.RB2
#define up_button_PORT PORTB.RB2

//dowen button configuration registers
#define dwn_button_TRIS TRISB.RB1
#define dwn_button_PORT PORTB.RB1

//counters time
#define BUTTON_CHECK_TIME 20

//data type that stores the state of the system while working
typedef enum {
        normal_mode,
        setting_mode
}mode_t;

//data type that stores the power state of the system
typedef enum {
    power_on,
    power_off
}power_t;

#endif
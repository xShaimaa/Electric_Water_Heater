#include "TMR1.h"

void TMR1_Init(){
    T1CON = 0x01;               //configuring the prescaler
    //laoding the timer required value for 10 ms delay
    TMR1H = 0xB1;
    TMR1L = 0xE0;
    TMR1IF_bit = 0;             //clearing the timer1 flag bit
    TMR1IE_bit = 1;             //enable timer1 iterrupt bit in PIE1 reg
    INTCON = 0xC0;              //configuring the Interrupt control reg
}
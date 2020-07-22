#ifndef TEMP_SENSOR_DISPLAY_H
#define TEMP_SENSOR_DISPLAY_H

//7 segments and its selection pins configurations
#define Seg_PORT PORTD
#define Seg_TRIS TRISD

#define Select1_PORT PORTA.RA5
#define Select1_TRIS TRISA.RA5

#define Select2_PORT PORTA.RA4
#define Select2_TRIS TRISA.RA4

//ADC channel configurations
#define ADC_TRIS TRISA.RA2
#define ADC_PORT PORTA.RA2

#define TEMP_SAMPLE 10
//counters time
#define TEMP_SAMPLE_PERIOD 10
#define ONES_TIME 1
#define TENS_TIME 2

//functions prototypes

/*setting up the 7 segments and selection pins configurations*/
void Seg_Init();                                                        

/*setting up the ADC*/
void ADC_begin();

/*function to calculate the aerage of the measured temp array*/
void average();

/*function that is used to return the tempreture sensor average reading,
 *the average is to taken from 10 values, each taken every 100ms*/
unsigned char Temp_samples (); 

/*function that returns the hex value equvilant for certin num*/
unsigned char Seg_Values(unsigned char v);        

/*function that is used to display the average of the last 10 readings
 *on two 7-seg. using a multiplixer to switch  between the ones and tens 7-seg.*/
void Sensor_Display (int temp);                                             

#endif
#include "Temp_Sensor_Display.h"

//variables
unsigned char temp_read,                                 //variable to store the current temp read
              ones, tens,                                //variables used to split the displayed temp to ones and tens 
              selection_counter,                         //counter to swwich between the 7-seg selection pins
              temp_counter,                              //counter to fill the array to store the samples
              Temp_Av[10],                               //array to store the temp samples
              Temp_Req,                                  //the required temp that is to be displayed
              Temp_Avg,                                  //variable used to store the current temp average
              Avg_counter = 0,                           //counter used to take the temp average for the last 10 samples
              Temp,                                      //variable used to store the temp sample
              Avg;                                       //variable to store the average of the last 10 temp samples
unsigned int  sum;                                       //aiable to sum the last 10 temp samples

void Seg_Init(){
    //PORTD is output for the 7-seg
    Seg_TRIS = 0x00;
    Seg_PORT = 0X00;
    //selction bits for the 7-seg are output
    Select1_TRIS = 0;                                    
    Select2_TRIS = 0;
    Select1_PORT = 0;
    Select2_PORT = 0;
}

void ADC_begin(){
    //using channel 2 in the ADC module setting it as input
    ADC_TRIS = 1;
    ADC_PORT = 1;
    // Initialize ADC module
    ADC_Init();  
}

void average(){
    int i;
    for (i=0; i<TEMP_SAMPLE; i++){
        sum += Temp_Av[i];
    }
    Avg = sum / TEMP_SAMPLE;
    sum=0;
}

unsigned char Temp_samples (){
    temp_counter ++;
    //store a new tempreture reading in the array every 100ms
    if (temp_counter == TEMP_SAMPLE_PERIOD){
        Temp = ADC_Read(2);
        Temp = Temp *4.89 / 10;
        Temp_Av[Avg_counter] = Temp;
        Avg_counter ++;
        if (Avg_counter == TEMP_SAMPLE) {
            Avg_counter = 0; 
        }
        average ();
        temp_counter = 0;
    }
    return Avg ;
}

unsigned char Seg_Values (unsigned char v)
{
    //determine the hex value for the 7seg. to display each num.
    switch(v){        
        case 0:
            return 0x3F;
            break;
        case 1:
            return 0x06;
            break;
        case 2:
            return 0x5B;
            break;
        case 3:
            return 0x4F;
            break;
        case 4:
            return 0x66;
            break;
        case 5:
            return 0x6D;
            break;
        case 6:
            return 0x7D;
            break;
        case 7:
            return 0x07;
            break;
        case 8:
            return 0x7F;
            break;
        case 9:
            return 0x6F;
            break;
        default:
            return 0;
            break;
    }
}

void Sensor_Display (int temp){
    selection_counter ++;
    //getting the number that is to be displayed on each 7seg.
    ones = temp % 10;
    tens = temp / 10;
    //the ones 7-seg. will be on on the first 10ms
    if (selection_counter == ONES_TIME){
        Select1_PORT = 1;
        Select2_PORT = 0;
        Seg_PORT = Seg_Values(ones);
    }
    //the tens 7-seg. will be on on the second 10ms
    else if (selection_counter == TENS_TIME){
        Select1_PORT = 0;
        Select2_PORT = 1;
        Seg_PORT = Seg_Values(tens);
        selection_counter = 0;
    }
}

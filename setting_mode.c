#include "setting_mode.h"
#include "main.h"
#include "Temp_Sensor_Display.h"

//variables
unsigned char button_counter;               //counter to check the states of the buttons every 100ms 
unsigned char seg_blink_counter;            //counter to blink the 7-segments every 1sec
unsigned int setting_break;                 //counter used to break the setting mode if 5sec passed without pressing a button
extern unsigned char set_temp;              //variable used to store the set temp. in the setting mode
extern mode_t mode;                         //data type that holds the mode state of the system
extern unsigned char EEPROM_flag = 0;       //flag to be set after setting  new temp.

void button_setting (){
    setting_break ++;
    button_counter ++;
    //checking the buttons state every 100ms
    if (button_counter == BUTTON_CHECK_TIME){
        button_counter = 0;
        if ((up_button_PORT ==0) && (set_temp <75) ){
           setting_break = 0;
           set_temp += 5;                        //each up press is +5
        }
        else if ((dwn_button_PORT ==0) && (set_temp > 35)){
           setting_break = 0;
           set_temp -= 5;                        //each down press is -5
        }
    }
    //after 5sec, break the setting mode and store the set temp in EEPROM 
    if (setting_break == SETTING_TIMEOUT) {
        setting_break = 0;
        mode = normal_mode;
        EEPROM_flag = 1;
    }
}

void seg_blink(){
    seg_blink_counter ++;
    //keep the 7-seg displaying during the first sec
    if (seg_blink_counter < SEG_DISPLAY_ON){
        Sensor_Display (set_temp);
    }
    //turn the 7-seg of for the second sec 
    else if (seg_blink_counter == SEG_DISPLAY_ON){
        Seg_PORT = 0X00;
        Select1_PORT = 0;
        Select2_PORT = 0;
    }
        //when the second sec passes, repeat the cycle all over
    else if (seg_blink_counter == SEG_DISPLAY_OFF){
        seg_blink_counter = 0;
    }
}

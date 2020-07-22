#ifndef SETTING_MODE_H_
#define SETTING_MODE_H_

//counter_time
#define SEG_DISPLAY_ON 100
#define SEG_DISPLAY_OFF 200
#define SETTING_TIMEOUT 500

/*function that checks the up nd down buttons every 100ms
 *and changes the temp. that is to be set,
 *every up or down press is represented with +5 or -5*/
void button_setting ();

/*funtion thet i ued to blink the 7-seg every 1sec
 * in the setting mode using a counter*/
void seg_blink();

#endif
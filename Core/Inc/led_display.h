#ifndef INC_LED_DISPLAY_H_
#define INC_LED_DISPLAY_H_

#include "main.h"

// Hàm điều khiển 6 LEDs đèn giao thông
void display_led_red_1(void);
void display_led_yellow_1(void);
void display_led_green_1(void);
void display_led_red_2(void);
void display_led_yellow_2(void);
void display_led_green_2(void);

void clear_all_leds(void);

// Hàm điều khiển 7-segment
void display_7seg(int num, int index);
void update_7seg_buffer(int index, int value);
void clear_all_7seg(void);

#endif /* INC_LED_DISPLAY_H_ */

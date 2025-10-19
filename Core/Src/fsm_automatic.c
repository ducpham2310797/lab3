/*
 * fsm_automatic.c
 *
 *  Created on: Oct 19, 2025
 *      Author: ACER
 */


#include "fsm_automatic.h"

// FSM states cho mode normal
#define INIT 0
#define RED_GREEN 1
#define RED_AMBER 2
#define GREEN_RED 3
#define AMBER_RED 4

static int status = INIT;
static int timer_counter_1 = 0;
static int timer_counter_2 = 0;

void fsm_automatic_run(void) {
    switch(status) {
        case INIT:
            // Khởi tạo
            status = RED_GREEN;
            timer_counter_1 = red_time;
            timer_counter_2 = green_time;
            break;

        case RED_GREEN:
            // Road 1: RED, Road 2: GREEN
            clear_all_leds();
            display_led_red_1();
            display_led_green_2();

            // Hiển thị thời gian đếm ngược
            update_7seg_buffer(0, timer_counter_1);
            update_7seg_buffer(1, timer_counter_2);

            // Đếm ngược
            timer_counter_1--;
            timer_counter_2--;

            // Chuyển sang trạng thái tiếp theo
            if(timer_counter_2 <= 0) {
                status = RED_AMBER;
                timer_counter_1 = red_time - green_time;
                timer_counter_2 = amber_time;
            }
            break;

        case RED_AMBER:
            // Road 1: RED, Road 2: AMBER
            clear_all_leds();
            display_led_red_1();
            display_led_yellow_2();

            update_7seg_buffer(0, timer_counter_1);
            update_7seg_buffer(1, timer_counter_2);

            timer_counter_1--;
            timer_counter_2--;

            if(timer_counter_2 <= 0) {
                status = GREEN_RED;
                timer_counter_1 = green_time;
                timer_counter_2 = red_time;
            }
            break;

        case GREEN_RED:
            // Road 1: GREEN, Road 2: RED
            clear_all_leds();
            display_led_green_1();
            display_led_red_2();

            update_7seg_buffer(0, timer_counter_1);
            update_7seg_buffer(1, timer_counter_2);

            timer_counter_1--;
            timer_counter_2--;

            if(timer_counter_1 <= 0) {
                status = AMBER_RED;
                timer_counter_1 = amber_time;
                timer_counter_2 = red_time - green_time;
            }
            break;

        case AMBER_RED:
            // Road 1: AMBER, Road 2: RED
            clear_all_leds();
            display_led_yellow_1();
            display_led_red_2();

            update_7seg_buffer(0, timer_counter_1);
            update_7seg_buffer(1, timer_counter_2);

            timer_counter_1--;
            timer_counter_2--;

            if(timer_counter_1 <= 0) {
                status = RED_GREEN;
                timer_counter_1 = red_time;
                timer_counter_2 = green_time;
            }
            break;
    }
}

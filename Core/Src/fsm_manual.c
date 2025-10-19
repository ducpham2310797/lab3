/*
 * fsm_manual.c
 *
 *  Created on: Oct 19, 2025
 *      Author: ACER
 */


#include "fsm_manual.h"

static int blink_counter = 0;
static int blink_status = 0;  // 0 = OFF, 1 = ON

void fsm_manual_run(void) {
    // Blink LEDs at 2Hz (toggle every 250ms = 25 timer ticks)
    blink_counter++;
    if(blink_counter >= 25) {
        blink_counter = 0;
        blink_status = !blink_status;
    }

    switch(current_mode) {
        case MODE_RED:
            // Hiển thị mode 2 trên 7-seg road 2
            update_7seg_buffer(1, 2);

            // Hiển thị giá trị red_time trên 7-seg road 1
            update_7seg_buffer(0, red_time);

            // Blink tất cả LED đỏ
            if(blink_status) {
                HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, GPIO_PIN_SET);
                HAL_GPIO_WritePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin, GPIO_PIN_SET);
            } else {
                HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin, GPIO_PIN_RESET);
            }

            // Tắt các LED khác
            HAL_GPIO_WritePin(LED_YELLOW_1_GPIO_Port, LED_YELLOW_1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(LED_YELLOW_2_GPIO_Port, LED_YELLOW_2_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin, GPIO_PIN_RESET);

            // Button INC để tăng giá trị
            if(is_button_pressed(BUTTON_INC)) {
                red_time++;
                if(red_time > 99) red_time = 1;
            }

            // Button SET để lưu giá trị
            if(is_button_pressed(BUTTON_SET)) {
                // Giá trị đã được lưu trong biến red_time
            }
            break;

        case MODE_AMBER:
            update_7seg_buffer(1, 3);
            update_7seg_buffer(0, amber_time);

            // Blink tất cả LED vàng
            if(blink_status) {
                HAL_GPIO_WritePin(LED_YELLOW_1_GPIO_Port, LED_YELLOW_1_Pin, GPIO_PIN_SET);
                HAL_GPIO_WritePin(LED_YELLOW_2_GPIO_Port, LED_YELLOW_2_Pin, GPIO_PIN_SET);
            } else {
                HAL_GPIO_WritePin(LED_YELLOW_1_GPIO_Port, LED_YELLOW_1_Pin, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(LED_YELLOW_2_GPIO_Port, LED_YELLOW_2_Pin, GPIO_PIN_RESET);
            }

            HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin, GPIO_PIN_RESET);

            if(is_button_pressed(BUTTON_INC)) {
                amber_time++;
                if(amber_time > 99) amber_time = 1;
            }
            break;

        case MODE_GREEN:
            update_7seg_buffer(1, 4);
            update_7seg_buffer(0, green_time);

            // Blink tất cả LED xanh
            if(blink_status) {
                HAL_GPIO_WritePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin, GPIO_PIN_SET);
                HAL_GPIO_WritePin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin, GPIO_PIN_SET);
            } else {
                HAL_GPIO_WritePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin, GPIO_PIN_RESET);
            }

            HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(LED_YELLOW_1_GPIO_Port, LED_YELLOW_1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(LED_YELLOW_2_GPIO_Port, LED_YELLOW_2_Pin, GPIO_PIN_RESET);

            if(is_button_pressed(BUTTON_INC)) {
                green_time++;
                if(green_time > 99) green_time = 1;
            }
            break;
    }
}

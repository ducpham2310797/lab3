/*
 * led_display.c
 *
 *  Created on: Oct 19, 2025
 *      Author: ACER
 */


#include "led_display.h"

// === ĐIỀU KHIỂN LEDs ĐÈN GIAO THÔNG ===

void display_led_red_1(void) {
    HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, GPIO_PIN_RESET);
}

void display_led_yellow_1(void) {
    HAL_GPIO_WritePin(LED_YELLOW_1_GPIO_Port, LED_YELLOW_1_Pin, GPIO_PIN_RESET);
}

void display_led_green_1(void) {
    HAL_GPIO_WritePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin, GPIO_PIN_RESET);
}

void display_led_red_2(void) {
    HAL_GPIO_WritePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin, GPIO_PIN_RESET);
}

void display_led_yellow_2(void) {
    HAL_GPIO_WritePin(LED_YELLOW_2_GPIO_Port, LED_YELLOW_2_Pin, GPIO_PIN_RESET);
}

void display_led_green_2(void) {
    HAL_GPIO_WritePin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin, GPIO_PIN_RESET);
}

void clear_all_leds(void) {
    HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_YELLOW_1_GPIO_Port, LED_YELLOW_1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_YELLOW_2_GPIO_Port, LED_YELLOW_2_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin, GPIO_PIN_SET);
}

// === ĐIỀU KHIỂN 7-SEGMENT QUA 74LS47 ===

void display_7seg(int num, int index) {
    if(num < 0) num = 0;
    if(num > 9) num = 9;

    // Tách num thành 4 bit BCD
    uint8_t bit0 = (num >> 0) & 0x01;
    uint8_t bit1 = (num >> 1) & 0x01;
    uint8_t bit2 = (num >> 2) & 0x01;
    uint8_t bit3 = (num >> 3) & 0x01;

    switch(index) {
        case 0: // LED 7-seg 0 (inputseg0)
            HAL_GPIO_WritePin(inputseg0_0_GPIO_Port, inputseg0_0_Pin, bit0);
            HAL_GPIO_WritePin(inputseg0_1_GPIO_Port, inputseg0_1_Pin, bit1);
            HAL_GPIO_WritePin(inputseg0_2_GPIO_Port, inputseg0_2_Pin, bit2);
            HAL_GPIO_WritePin(inputseg0_3_GPIO_Port, inputseg0_3_Pin, bit3);
            break;
        case 1: // LED 7-seg 1 (inputseg1)
            HAL_GPIO_WritePin(inputseg1_0_GPIO_Port, inputseg1_0_Pin, bit0);
            HAL_GPIO_WritePin(inputseg1_1_GPIO_Port, inputseg1_1_Pin, bit1);
            HAL_GPIO_WritePin(inputseg1_2_GPIO_Port, inputseg1_2_Pin, bit2);
            HAL_GPIO_WritePin(inputseg1_3_GPIO_Port, inputseg1_3_Pin, bit3);
            break;
        case 2: // LED 7-seg 2 (inputseg2)
            HAL_GPIO_WritePin(inputseg2_0_GPIO_Port, inputseg2_0_Pin, bit0);
            HAL_GPIO_WritePin(inputseg2_1_GPIO_Port, inputseg2_1_Pin, bit1);
            HAL_GPIO_WritePin(inputseg2_2_GPIO_Port, inputseg2_2_Pin, bit2);
            HAL_GPIO_WritePin(inputseg2_3_GPIO_Port, inputseg2_3_Pin, bit3);
            break;
        case 3: // LED 7-seg 3 (inputseg3)
            HAL_GPIO_WritePin(inputseg3_0_GPIO_Port, inputseg3_0_Pin, bit0);
            HAL_GPIO_WritePin(inputseg3_1_GPIO_Port, inputseg3_1_Pin, bit1);
            HAL_GPIO_WritePin(inputseg3_2_GPIO_Port, inputseg3_2_Pin, bit2);
            HAL_GPIO_WritePin(inputseg3_3_GPIO_Port, inputseg3_3_Pin, bit3);
            break;
    }
}

void update_7seg_buffer(int index, int value) {
    if(value < 0) value = 0;
    if(value > 99) value = 99;

    int tens = value / 10;
    int units = value % 10;

    if(index == 0) {  // Road 1
        display_7seg(tens, 0);
        display_7seg(units, 1);
    } else if(index == 1) {  // Road 2
        display_7seg(tens, 2);
        display_7seg(units, 3);
    }
}

void clear_all_7seg(void) {
    display_7seg(0, 0);
    display_7seg(0, 1);
    display_7seg(0, 2);
    display_7seg(0, 3);
}

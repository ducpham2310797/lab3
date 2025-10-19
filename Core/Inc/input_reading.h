/*
 * input_reading.h
 *
 *  Created on: Oct 19, 2025
 *      Author: ACER
 */

#ifndef INC_INPUT_READING_H_
#define INC_INPUT_READING_H_
#include "main.h"  // ← THÊM DÒNG NÀY
#define N0_OF_BUTTONS 3

#define BUTTON_MODE 0    // button0 - PA9
#define BUTTON_INC 1     // button1 - PA10
#define BUTTON_SET 2     // button2 - PA11

void button_reading(void);
unsigned char is_button_pressed(uint8_t index);
unsigned char is_button_pressed_1s(unsigned char index);

#endif /* INC_INPUT_READING_H_ */

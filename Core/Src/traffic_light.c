/*
 * traffic_light.c
 *
 *  Created on: Oct 19, 2025
 *      Author: ACER
 */


#include "main.h"
#include "global.h"
#include "led_display.h"

// Variables


// Timer counters
int timer_counter = 0;
int led_buffer_road1 = 0;
int led_buffer_road2 = 0;

// FSM states cho mode normal
#define INIT 0
#define RED_GREEN 1
#define RED_AMBER 2
#define GREEN_RED 3
#define AMBER_RED 4

int status = INIT;

/*
 * LEDs_display.c
 *
 *  Created on: 5 Dec 2022
 *      Author: Admin
 */

#include "LEDs_display.h"

void red1_on() {
	HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, LED_ON);
	HAL_GPIO_WritePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin, LED_OFF);
	HAL_GPIO_WritePin(LED_AMBER_1_GPIO_Port, LED_AMBER_1_Pin, LED_OFF);
}

void green1_on() {
	HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, LED_OFF);
	HAL_GPIO_WritePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin, LED_ON);
	HAL_GPIO_WritePin(LED_AMBER_1_GPIO_Port, LED_AMBER_1_Pin, LED_OFF);
}

void amber1_on() {
	HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, LED_OFF);
	HAL_GPIO_WritePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin, LED_OFF);
	HAL_GPIO_WritePin(LED_AMBER_1_GPIO_Port, LED_AMBER_1_Pin, LED_ON);
}

void red2_on() {
	HAL_GPIO_WritePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin, LED_ON);
	HAL_GPIO_WritePin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin, LED_OFF);
	HAL_GPIO_WritePin(LED_AMBER_2_GPIO_Port, LED_AMBER_2_Pin, LED_OFF);
}

void green2_on() {
	HAL_GPIO_WritePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin, LED_OFF);
	HAL_GPIO_WritePin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin, LED_ON);
	HAL_GPIO_WritePin(LED_AMBER_2_GPIO_Port, LED_AMBER_2_Pin, LED_OFF);
}

void amber2_on() {
	HAL_GPIO_WritePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin, LED_OFF);
	HAL_GPIO_WritePin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin, LED_OFF);
	HAL_GPIO_WritePin(LED_AMBER_2_GPIO_Port, LED_AMBER_2_Pin, LED_ON);
}

void LEDsDisplay() {
	int LEDCycle = RED_time + GREEN_time + AMBER_time;

	SCH_Add_Task(red1_on, 0, LEDCycle);
	SCH_Add_Task(green1_on, RED_time, LEDCycle);
	SCH_Add_Task(amber1_on, RED_time + GREEN_time, LEDCycle);

	SCH_Add_Task(green2_on, 0, LEDCycle);
	SCH_Add_Task(amber2_on, GREEN_time, LEDCycle);
	SCH_Add_Task(red2_on, GREEN_time + AMBER_time, LEDCycle);
}

void LEDsOn() {
	HAL_GPIO_WritePin(GPIOA, 0xFC, LED_ON);
}

void LEDsOff() {
	HAL_GPIO_WritePin(GPIOA, 0xFC, LED_OFF);
}

void LEDsBlinking() {
	SCH_Add_Task(LEDsOn, 0, LED_blinking_time * 2);
	SCH_Add_Task(LEDsOff, LED_blinking_time, LED_blinking_time * 2);
}

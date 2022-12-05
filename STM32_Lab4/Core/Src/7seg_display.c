/*
 * 7seg_display.c
 *
 *  Created on: 5 Dec 2022
 *      Author: Admin
 */

#include "7seg_display.h"

int led_buffer[4] = {1, 2, 3, 4};
int h_count_down = 0;
int v_count_down = 0;
int hState = AUTO_INIT;
int vState = AUTO_INIT;

void display7SEG(int num) {
	switch (num) {
		case 0:
			HAL_GPIO_WritePin(GPIOB, 0B0111111, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, 0B1000000, GPIO_PIN_SET);
			break;
		case 1:
			HAL_GPIO_WritePin(GPIOB, 0B0000110, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, 0B1111001, GPIO_PIN_SET);
			break;
		case 2:
			HAL_GPIO_WritePin(GPIOB, 0B1011011, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, 0B0100100, GPIO_PIN_SET);
			break;
		case 3:
			HAL_GPIO_WritePin(GPIOB, 0B1001111, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, 0B0110000, GPIO_PIN_SET);
			break;
		case 4:
			HAL_GPIO_WritePin(GPIOB, 0B1100110, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, 0B0011001, GPIO_PIN_SET);
			break;
		case 5:
			HAL_GPIO_WritePin(GPIOB, 0B1101101, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, 0B0010010, GPIO_PIN_SET);
			break;
		case 6:
			HAL_GPIO_WritePin(GPIOB, 0B1111101, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, 0B0000010, GPIO_PIN_SET);
			break;
		case 7:
			HAL_GPIO_WritePin(GPIOB, 0B0000111, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, 0B1111000, GPIO_PIN_SET);
			break;
		case 8:
			HAL_GPIO_WritePin(GPIOB, 0B1111111, GPIO_PIN_RESET);
			break;
		case 9:
			HAL_GPIO_WritePin(GPIOB, 0B1101111, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, 0B0010000, GPIO_PIN_SET);
			break;
		default:
			HAL_GPIO_WritePin(GPIOB, 0B1111111, GPIO_PIN_SET);
			break;
	}
}

void update7SEG(int index){
    switch (index){
        case 0:
            //Display the first 7SEG with led_buffer[0]
            display7SEG(led_buffer[0]);
            break;
        case 1:
            //Display the second 7SEG with led_buffer[1]
            display7SEG(led_buffer[1]);
            break;
        case 2:
            //Display the third 7SEG with led_buffer[2]
            display7SEG(led_buffer[2]);
            break;
        case 3:
            //Display the forth 7SEG with led_buffer[3]
            display7SEG(led_buffer[3]);
            break;
        default:
            break;
    }
}

//void updateBufferForMode1() {
//	led_buffer[0] = currentCounter(0) / 1000;
//	led_buffer[1] = (currentCounter(0) / 100) % 10;
//	led_buffer[2] = currentCounter(1) / 1000;
//	led_buffer[3] = (currentCounter(1) / 100) % 10;
//}

void updateBufferForIncTime() {
	// 2 7seg LEDs to display the value
	led_buffer[0] = time_count / 10;
	led_buffer[1] = time_count % 10;

	// 2 7seg LEDs to display the mode
	led_buffer[2] = 0;
	switch (mode) {
		case MODE_2:
			led_buffer[3] = 2;
			break;
		case MODE_3:
			led_buffer[3] = 3;
			break;
		case MODE_4:
			led_buffer[3] = 4;
			break;
		case INC_RED:
			led_buffer[3] = 2;
			break;
		case INC_AMBER:
			led_buffer[3] = 3;
			break;
		case INC_GREEN:
			led_buffer[3] = 4;
			break;
		default:
			break;
	}
}

void SEG0_on() {
	HAL_GPIO_WritePin(GPIOA, 0xE00, SEG_OFF);
	HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, SEG_ON);
	update7SEG(0);
}

void SEG1_on() {
	HAL_GPIO_WritePin(GPIOA, 0xD00, SEG_OFF);
	HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, SEG_ON);
	update7SEG(1);
}

void SEG2_on() {
	HAL_GPIO_WritePin(GPIOA, 0xB00, SEG_OFF);
	HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, SEG_ON);
	update7SEG(2);
}

void SEG3_on() {
	HAL_GPIO_WritePin(GPIOA, 0x700, SEG_OFF);
	HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, SEG_ON);
	update7SEG(3);
}

void run7SEG() {
	SCH_Add_Task(SEG0_on, 0, SEG_switching_time * 4);
	SCH_Add_Task(SEG1_on, SEG_switching_time, SEG_switching_time * 4);
	SCH_Add_Task(SEG2_on, SEG_switching_time * 2, SEG_switching_time * 4);
	SCH_Add_Task(SEG3_on, SEG_switching_time * 3, SEG_switching_time * 4);
}


void countDownTime() {
	switch (hState) {
		case AUTO_INIT:
			h_count_down = RED_time / 1000;
			hState = AUTO_RED;
			break;

		case AUTO_RED:
			if (h_count_down == 1) {
				h_count_down = GREEN_time / 1000;
				hState = AUTO_GREEN;
			}
			else h_count_down--;
			break;

		case AUTO_GREEN:
			if (h_count_down == 1) {
				h_count_down = AMBER_time / 1000;
				hState = AUTO_AMBER;
			}
			else h_count_down--;
			break;

		case AUTO_AMBER:
			if (h_count_down == 1) {
				h_count_down = RED_time / 1000;
				hState = AUTO_RED;
			}
			else h_count_down--;
			break;

		default:
			break;
	}

	switch (vState) {
		case AUTO_INIT:
			v_count_down = GREEN_time / 1000;
			vState = AUTO_GREEN;
			break;

		case AUTO_RED:
			if (v_count_down == 1) {
				v_count_down = GREEN_time / 1000;
				vState = AUTO_GREEN;
			}
			else v_count_down--;
			break;

		case AUTO_GREEN:
			if (v_count_down == 1) {
				v_count_down = AMBER_time / 1000;
				vState = AUTO_AMBER;
			}
			else v_count_down--;
			break;

		case AUTO_AMBER:
			if (v_count_down == 1) {
				v_count_down = RED_time / 1000;
				vState = AUTO_RED;
			}
			else v_count_down--;
			break;

		default:
			break;
	}
}

void updateBufferForMode1() {
	led_buffer[0] = h_count_down / 10;
	led_buffer[1] = h_count_down % 10;
	led_buffer[2] = v_count_down / 10;
	led_buffer[3] = v_count_down % 10;
}

void runCount() {
	SCH_Add_Task(countDownTime, 0, 1000);
}

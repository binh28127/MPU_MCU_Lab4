/*
 * button_reading.c
 *
 *  Created on: 5 Dec 2022
 *      Author: Admin
 */

#include "button_reading.h"

int button_state[NO_OF_BUTTONS] = { 0, 0, 0 };
int button_flag[NO_OF_BUTTONS];
GPIO_PinState key_reg[NO_OF_BUTTONS][4];
int counterForKeyPress[NO_OF_BUTTONS];

int isButtonPressed(int button) {
	if (button_flag[button]) {
		button_flag[button] = 0;
		return 1;
	}
	else return 0;
}

void setTimerForButton(int button) {
	counterForKeyPress[button] = timerForKeyPress / timerCycle;
}

void fsm_button_processing(int button) {
	switch (button_state[button]) {
		case BUTTON_IS_RELEASED:
			// Press button
			if (key_reg[button][2] == PRESSED_STATE) {
				key_reg[button][3] = PRESSED_STATE;
				button_state[button] = BUTTON_IS_PRESSED;
				button_flag[button] = 1;
				setTimerForButton(button);
			}
			break;

		case BUTTON_IS_PRESSED:
			// Press button, then release
			if (key_reg[button][2] == NORMAL_STATE) {
				key_reg[button][3] = NORMAL_STATE;
				button_state[button] = BUTTON_IS_RELEASED;
			}
			// Press and hold button
			else {
				counterForKeyPress[button]--;
				if (!counterForKeyPress[button]) {
					button_state[button] = BUTTON_IS_PRESSED;
					button_flag[button] = 1;
					setTimerForButton(button);
				}
			}
			break;

		default:
			break;
	}
}

void getKeyInput() {
	for (int button = 0; button < NO_OF_BUTTONS; button++) {
		key_reg[button][0] = key_reg[button][1];
		key_reg[button][1] = key_reg[button][2];
		switch (button) {
			case BUTTON_1:
				key_reg[button][2] = HAL_GPIO_ReadPin(BUTTON_1_GPIO_Port, BUTTON_1_Pin);
				break;
			case BUTTON_2:
				key_reg[button][2] = HAL_GPIO_ReadPin(BUTTON_2_GPIO_Port, BUTTON_2_Pin);
				break;
			case BUTTON_3:
				key_reg[button][2] = HAL_GPIO_ReadPin(BUTTON_3_GPIO_Port, BUTTON_3_Pin);
				break;
			default:
				break;
		}

		if ((key_reg[button][0] == key_reg[button][1]) && (key_reg[button][1] == key_reg[button][2])) {
			fsm_button_processing(button);
		}
	}
}

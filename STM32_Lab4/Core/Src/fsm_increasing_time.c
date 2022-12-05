/*
 * fsm_increasing_time.c
 *
 *  Created on: 5 Dec 2022
 *      Author: Admin
 */

#include "fsm_increasing_time.h"

void fsmIncTimeRun() {
	switch (mode) {
		case INC_RED:
			// LEDs blinking
			LEDsBlinking();

			// Update time for 7seg LEDs
			updateBufferForIncTime();

			// 1st button is pressed, switch to mode3
			if (isButtonPressed(BUTTON_1)) {
				mode = MODE_3;
			}

			// 3rd button is pressed, set the value for the red LEDs
			if (isButtonPressed(BUTTON_3)) {
				mode = MODE_2;
				RED_time = time_count * 1000;
			}

			// 2nd button is pressed, increase the time duration value of the red LEDs
			if (isButtonPressed(BUTTON_2)) {
				if (time_count > 99) time_count = 0;
				time_count++;
			}

			break;

		case INC_AMBER:
			// LEDs blinking
			LEDsBlinking();

			// Update time for 7seg LEDs
			updateBufferForIncTime();

			// 1st button is pressed, switch to mode3
			if (isButtonPressed(BUTTON_1)) {
				mode = MODE_4;
			}

			// 3rd button is pressed, set the value for the amber LEDs
			if (isButtonPressed(BUTTON_3)) {
				mode = MODE_3;
				AMBER_time = time_count * 1000;
			}

			// 2nd button is pressed, increase the time duration value of the amber LEDs
			if (isButtonPressed(BUTTON_2)) {
				if (time_count > 99) time_count = 0;
				time_count++;
			}

			break;

		case INC_GREEN:
			// LEDs blinking
			LEDsBlinking();

			// Update time for 7seg LEDs
			updateBufferForIncTime();

			// 1st button is pressed, switch to mode3
			if (isButtonPressed(BUTTON_1)) {
				mode = MODE_1;
			}

			// 3rd button is pressed, set the value for the green LEDs
			if (isButtonPressed(BUTTON_3)) {
				mode = MODE_4;
				GREEN_time = time_count * 1000;
			}

			// 2nd button is pressed, increase the time duration value of the green LEDs
			if (isButtonPressed(BUTTON_2)) {
				if (time_count > 99) time_count = 0;
				time_count++;
			}

			break;

		default:
			break;
	}
}

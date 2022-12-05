/*
 * fsm_traffic.c
 *
 *  Created on: 5 Dec 2022
 *      Author: Admin
 */

#include "fsm_traffic.h"

int time_count = 0;

void fsmTrafficRun() {
	switch (mode) {
		case MODE_INIT:
			mode = MODE_1;
			SCH_Init();
			LEDsDisplay();
			run7SEG();
			runCount();
			break;

		case MODE_1:
			if (isButtonPressed(BUTTON_1)) {
				mode = MODE_2;
				SCH_Init();
				LEDsBlinking();
				run7SEG();
			}

			// Update time for 7seg LEDs
			updateBufferForMode1();

			break;

		case MODE_2:
			if (isButtonPressed(BUTTON_1)) {
				mode = MODE_3;
			}

			// Update time for 7seg LEDs
			time_count = RED_time / 1000;
			updateBufferForIncTime();

			// 2nd button is pressed, increase the time duration value of the red LEDs
			if (isButtonPressed(BUTTON_2)) {
				mode = INC_RED;
				time_count++;
			}

			break;

		case MODE_3:
			if (isButtonPressed(BUTTON_1)) {
				mode = MODE_4;
			}

			// Update time for 7seg LEDs
			time_count = AMBER_time / 1000;
			updateBufferForIncTime();

			// 2nd button is pressed, increase the time duration value of the amber LEDs
			if (isButtonPressed(BUTTON_2)) {
				mode = INC_AMBER;
				time_count++;
			}

			break;

		case MODE_4:
			if (isButtonPressed(BUTTON_1)) {
				mode = MODE_1;
				SCH_Init();
				LEDsDisplay();
				run7SEG();
				runCount();
			}

			// Update time for 7seg LEDs
			time_count = GREEN_time / 1000;
			updateBufferForIncTime();

			// 2nd button is pressed, increase the time duration value of the green LEDs
			if (isButtonPressed(BUTTON_2)) {
				mode = INC_GREEN;
				time_count++;
			}

			break;

		default:
			break;
	}
}

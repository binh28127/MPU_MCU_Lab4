/*
 * button_reading.h
 *
 *  Created on: 5 Dec 2022
 *      Author: Admin
 */

#ifndef INC_BUTTON_READING_H_
#define INC_BUTTON_READING_H_

#include "global.h"
#include "main.h"

#define BUTTON_IS_RELEASED		0
#define BUTTON_IS_PRESSED		1

int isButtonPressed(int button);
void getKeyInput();

#endif /* INC_BUTTON_READING_H_ */

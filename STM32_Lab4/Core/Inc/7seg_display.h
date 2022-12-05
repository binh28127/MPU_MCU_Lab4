/*
 * 7seg_display.h
 *
 *  Created on: 5 Dec 2022
 *      Author: Admin
 */

#ifndef INC_7SEG_DISPLAY_H_
#define INC_7SEG_DISPLAY_H_

#include "global.h"
#include "main.h"

extern int h_count_down;
extern int v_count_down;

void run7SEG();
void updateBufferForMode1();
void updateBufferForIncTime();
void runCount();

#endif /* INC_7SEG_DISPLAY_H_ */

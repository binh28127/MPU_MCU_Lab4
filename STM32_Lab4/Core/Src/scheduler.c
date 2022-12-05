/*
 * scheduler.c
 *
 *  Created on: Nov 26, 2022
 *      Author: Admin
 */

#include "scheduler.h"

uint32_t TimerCycle = 10;

sTask SCH_tasks_G[SCH_MAX_TASKS];
uint32_t current_tasks = 0;

void SCH_Init(void) {
	for (uint32_t i = 0; i < current_tasks; i++) {
		SCH_Delete_Task(i);
	}
	current_tasks = 0;
}

void SCH_Add_Task(void (*pFunction)(void), const uint32_t DELAY, const uint32_t PERIOD) {
	if (current_tasks < SCH_MAX_TASKS) {

		SCH_tasks_G[current_tasks].pTask = pFunction;
		SCH_tasks_G[current_tasks].Delay = DELAY / TimerCycle;
		SCH_tasks_G[current_tasks].Period = PERIOD / TimerCycle;
		SCH_tasks_G[current_tasks].RunMe = 0;
		SCH_tasks_G[current_tasks].TaskID = current_tasks;

		current_tasks++;
	}
}

void SCH_Dispatch_Tasks(void) {
	for (uint32_t i = 0; i < current_tasks; i++) {

		if (SCH_tasks_G[i].RunMe > 0) {

			// Run the next task
			(*SCH_tasks_G[i].pTask)();
			SCH_tasks_G[i].RunMe--;

			// Delete one-shot task after running
			if (!SCH_tasks_G[i].Period) {
				SCH_Delete_Task(i);
			}
		}
	}
}

void SCH_Update(void) {
	for (uint32_t i = 0; i < current_tasks; i++) {

		// Not yet ready to run, decrement the delay counter
		if (SCH_tasks_G[i].Delay > 0) {
			SCH_tasks_G[i].Delay--;

		} else {
			// The task is due to run, schedule periodic tasks to run again
			SCH_tasks_G[i].Delay = SCH_tasks_G[i].Period;
			SCH_tasks_G[i].RunMe++;
		}
	}
}

void SCH_Delete_Task(const uint32_t TASK_INDEX) {
	// Shift the tasks right of the TASK_INDEX to the left
	for (uint32_t i = TASK_INDEX; i < current_tasks - 1; i++) {

		SCH_tasks_G[i].pTask = SCH_tasks_G[i + 1].pTask;
		SCH_tasks_G[i].Delay = SCH_tasks_G[i + 1].Delay;
		SCH_tasks_G[i].Period = SCH_tasks_G[i + 1].Period;
		SCH_tasks_G[i].RunMe = SCH_tasks_G[i + 1].RunMe;
		SCH_tasks_G[i].TaskID = SCH_tasks_G[i + 1].TaskID - 1;
	}

	// Reset the TASK_INDEX location
	SCH_tasks_G[current_tasks - 1].pTask = 0x0000;
	SCH_tasks_G[current_tasks - 1].Delay = 0;
	SCH_tasks_G[current_tasks - 1].Period = 0;
	SCH_tasks_G[current_tasks - 1].RunMe = 0;
	SCH_tasks_G[current_tasks - 1].TaskID = 0;

	current_tasks--;
}

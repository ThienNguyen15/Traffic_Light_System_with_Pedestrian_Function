/*
 * software_timer.h
 *
 *  Created on: Nov 28, 2023
 *      Author: Le Van Phuc			- 2152241
 *      		Nguyen Quang Thien	- 2152994
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#include "main.h"
#include "global.h"

int Current_Timer_Counter(int timer);

int isTimerUp(int timer);

void setFlag(int timer);

void setTimer(int timer, int duration);

void timerRun(void);

#endif /* INC_SOFTWARE_TIMER_H_ */

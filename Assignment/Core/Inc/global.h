/*
 * global.h
 *
 *  Created on: Oct 22, 2023
 *      Author: Le Van Phuc			- 2152241
 *      		Nguyen Quang Thien	- 2152994
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "main.h"
#include"button.h"
#include"software_timer.h"
#include"displayLed.h"
#include "fsm_normal_state.h"
#include "scheduler.h"
#include "fsm_pedestrian.h"
#include "buzzer.h"

#define INIT 		0

#define RedGreen  	1
#define RedAmber  	2
#define GreenRed  	3
#define AmberRed  	4

#define TIMER	  	8

#define ManRed		10
#define ManAmber	11
#define ManGreen	12

#define Pedestrian_INIT 	14
#define Pedestrian_RED		15
#define Pedestrian_GREEN	16

extern int timeRed;
extern int timeYellow;
extern int timeGreen;

extern int status;

extern int time1,time2;

extern int pedestrian_flag;

extern TIM_HandleTypeDef htim3;

extern int buzzerValue;

extern int frequency;

extern int frequency1;

extern int freq[11];

extern flag;

extern UART_HandleTypeDef huart2;

#endif /* INC_GLOBAL_H_ */

/*
 * global.c
 *
 *  Created on: Oct 22, 2023
 *      Author: Le Van Phuc			- 2152241
 *      		Nguyen Quang Thien	- 2152994
 */

#include "global.h"

int timeRed = 5;

int timeYellow = 2;

int timeGreen = 3;

int status = INIT;

int time1, time2 = 0;

int pedestrian_flag = Pedestrian_INIT;

int buzzerValue = 0;

int frequency = -1; // Array delay

int frequency1 = 0; // Off duty-cycle

int freq[11] = {30, 25, 20, 15, 10, 6, 5, 4, 3, 2, 1};

int flag = 0;

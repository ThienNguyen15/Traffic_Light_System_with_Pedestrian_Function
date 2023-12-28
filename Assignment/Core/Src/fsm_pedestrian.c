/*
 * fsm_pedestrian.c
 *
 *  Created on: Nov 28, 2023
 *      Author: Le Van Phuc			- 2152241
 *      		Nguyen Quang Thien	- 2152994
 */

#include "global.h"

void fsm_pedestrian(void)
{
	switch(pedestrian_flag)
	{
		case Pedestrian_INIT:
			buzzer(0);

			frequency = -1;
			frequency1 = 0;
			flag = 0;
			setFlag(4);

			clearPedestrian();
			break;

		case Pedestrian_RED:
			buzzer(0);

			frequency = -1;
			frequency1 = 0;
			flag = 0;
			setFlag(4);

			if(isTimerUp(3) == 1)
				pedestrian_flag = Pedestrian_INIT;

			displayPedestrianRed();
			break;

		case Pedestrian_GREEN:
			if(isTimerUp(3) == 1)
				pedestrian_flag = Pedestrian_INIT;

			displayPedestrianGreen();

			if(isTimerUp(4) == 1)
			{
				frequency1 = 1;
				frequency += 1;
				setTimer(4, 50);
				setTimer(5, freq[frequency]);
				setTimer(6, 5);
			}

			if(frequency1 == 1)
			{
				if(isTimerUp(6) == 1)
				{
					buzzer(0);
					setTimer(5, freq[frequency]);
					frequency1++;
				}
				else
					buzzer(buzzerValue);
			}
			if(frequency1 == 2)
			{
				if(isTimerUp(5) == 1)
				{
					buzzer(buzzerValue);
					setTimer(6, 5);
					frequency1 = 1;
				}
				else
					buzzer(0);
			}
			break;

		default:
			break;
	}
}

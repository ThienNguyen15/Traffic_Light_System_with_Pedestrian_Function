/*
 * fsm_normal_state.c
 *
 *  Created on: Oct 22, 2023
 *      Author: Le Van Phuc			- 2152241
 *      		Nguyen Quang Thien	- 2152994
 */

#include "global.h"
#include<math.h>

void increase()
{
	time1++;
	if(time1 > 99)
		time1 = 1;
}

void balance(int RED, int AMBER, int GREEN)
{
	if(RED > timeRed)
	{
		timeYellow	= round( ( (float)(timeYellow * 1.0f) * (float)( (RED * 1.0f) / (timeRed * 1.0f) ) ) );
		timeGreen	= round( ( (float)(timeGreen * 1.0f) * (float)( (RED * 1.0f) / (timeRed * 1.0f) ) ) );
		timeRed		= RED;
	}
	else if(AMBER > timeYellow)
	{
		timeRed		= round( ( (float)(timeRed * 1.0f) * (float)( (AMBER * 1.0f) / (timeYellow * 1.0f) ) ) ) ;
		timeGreen	= round( ( (float)(timeGreen * 1.0f) * (float)( (AMBER * 1.0f) / (timeYellow * 1.0f) ) ) );
		timeYellow	= AMBER;
	}
	else if(GREEN > timeGreen)
	{
		timeRed		= round( ( (float)(timeRed * 1.0f) * (float)( (GREEN * 1.0f) / (timeGreen * 1.0f) ) ) );
		timeYellow	= round( ( (float)(timeYellow * 1.0f) * (float)( (GREEN * 1.0f) / (timeGreen * 1.0f) ) ) );
		timeGreen	= GREEN;
	}
	else if(RED < timeRed)
	{
		timeYellow	= round( (float)(RED * 1.0f) / (5 * 1.0f) ) * (float)(2 * 1.0f);
		timeGreen	= round( (float)(RED * 1.0f) / (5 * 1.0f) ) * (float)(3 * 1.0f);
		timeRed		= RED;
	}
	else if(AMBER < timeYellow)
	{
		timeRed		= round( (float)(AMBER * 1.0f) / (2 * 1.0f) ) * (float)(5 * 1.0f);
		timeGreen	= round( (float)(AMBER * 1.0f) / (2 * 1.0f) ) * (float)(3 * 1.0f);
		timeYellow	= AMBER;
	}
	else if(GREEN < timeGreen)
	{
		timeRed		= round( (float)(GREEN * 1.0f) / (3 * 1.0f) ) * (float)(5 * 1.0f);
		timeYellow	= round( (float)(GREEN * 1.0f) / (3 * 1.0f) ) * (float)(2 * 1.0f);
		timeGreen	= GREEN;
	}
}

void normalState(void)
{
	char str[50];
	switch(status)
	{
	case INIT:
		status = RedGreen;

		setTimer(0, timeGreen * 100);
		setTimer(1, 1);

		time1 = timeRed;
		time2 = timeGreen;
		break;

	case RedGreen:
		displayRed1();
		displayGreen2();

		if(isTimerUp(1) == 1)
		{	// Update Time
			HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "\r\n!7SEG_LED1 - LED_RED:   %d#\r\n",time1), 500);
			HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "\r\n!7SEG_LED2 - LED_GREEN: %d#\r\n\n\n",time2), 500);

			time1--;
			time2--;

			setTimer(1, 100);
		}

		if(isTimerUp(0) == 1)
		{	// Transit State
			status = RedAmber;

			setTimer(0, timeYellow * 100);
			setTimer(1, 1);

			time1 = timeYellow;
			time2 = timeYellow;
		}


		if(Is_Button_Pressed(1))
		{
			status = ManRed;

			time1 = timeRed;
			time2 = 2;

			clearAllLed1();
			clearAllLed2();

			setTimer(1, 100);
			setTimer(2, 25);
			setTimer(7,500);
		}
		if(Is_Button_Pressed(0))
		{
			pedestrian_flag = Pedestrian_RED;
			setTimer(3, (timeRed + timeGreen) * 100);
		}
		break;

	case RedAmber:
		displayRed1();
		displayYellow2();

		if(isTimerUp(1) == 1)
		{	// Update Time
			HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "\r\n!7SEG_LED1 - LED_RED:    %d#\r\n",time1), 500);
			HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "\r\n!7SEG_LED12 - LED_AMBER: %d#\r\n\n\n",time2), 500);

			time1--;
			time2--;

			setTimer(1, 100);
		}

		if(isTimerUp(0)==1)
		{	// Transit State
			status = GreenRed;

			setTimer(0, timeGreen * 100);
			setTimer(1, 1);

			time1 = timeGreen;
			time2 = timeRed;

			if(pedestrian_flag == Pedestrian_RED)
				pedestrian_flag = Pedestrian_GREEN;
		}


		if(Is_Button_Pressed(1))
		{
			status = ManRed;

			time1 = timeRed;
			time2 = 2;

			clearAllLed1();
			clearAllLed2();

			setTimer(1, 100);
			setTimer(2, 25);
			setTimer(7,500);
		}

		if(Is_Button_Pressed(0))
		{
			pedestrian_flag = Pedestrian_RED;
			setTimer(3, (timeRed + timeGreen) * 100);
		}
		break;

	case GreenRed:
		displayGreen1();
		displayRed2();

		if(timeYellow < 5 && time1 <= 5 - timeYellow && flag == 0 && pedestrian_flag == Pedestrian_GREEN)
		{
			flag = 1;
			setTimer(4, 1);
		}

		if(isTimerUp(1)==1)
		{	// Update Time
			HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "\r\n!7SEG_LED1 - LED_GREEN: %d#\r\n",time1), 500);
			HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "\r\n!7SEG_LED2 - LED_RED:   %d#\r\n\n\n",time2), 500);

			time1--;
			time2--;

			setTimer(1, 100);
		}

		if(isTimerUp(0) == 1)
		{	// Transit State
			status = AmberRed;

			setTimer(0, timeYellow * 100);
			setTimer(1, 1);

			time1 = timeYellow;
			time2 = timeYellow;
		}

		if(timeYellow < 5 && time1 <= 5 - timeYellow)
				buzzerValue = 512 * (5- timeYellow - time1);

		if(Is_Button_Pressed(1))
		{
			status = ManRed;

			time1 = timeRed;
			time2 = 2;

			clearAllLed1();
			clearAllLed2();

			setTimer(1, 100);
			setTimer(2, 25);
			setTimer(7,500);
		}

		if(Is_Button_Pressed(0))
		{
			pedestrian_flag = Pedestrian_GREEN;
			setTimer(3, (timeRed + timeGreen) * 100);
		}
		break;

	case AmberRed:
		displayYellow1();
		displayRed2();

		if (timeYellow >= 5 && time1 == 5 && flag == 0 && pedestrian_flag == Pedestrian_GREEN)
		{
			flag = 1;
			setTimer(4, 1);
		}

		if(isTimerUp(1) == 1)
		{	// Update Time
			HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "\r\n!7SEG_LED1 - LED_AMBER: %d#\r\n",time1), 500);
			HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "\r\n!7SEG_LED2 - LED_RED:   %d#\r\n\n\n",time2), 500);

			time1--;
			time2--;

			setTimer(1, 100);
		}

		if(isTimerUp(0) == 1)
		{	// Transit State
			status = RedGreen;

			setTimer(0, timeGreen * 100);
			setTimer(1, 1);

			time1 = timeRed;
			time2 = timeGreen;

			if(pedestrian_flag == Pedestrian_GREEN)
				pedestrian_flag = Pedestrian_RED;
		}


		if (timeYellow >= 5 && time1 <= 5)
			buzzerValue = 512 * (5 - time1);

		if(timeYellow < 5)
			buzzerValue += 256 * (5 - time1);


		if(Is_Button_Pressed(1))
		{
			status = ManRed;

			time1 = timeRed;
			time2 = 2;

			clearAllLed1();
			clearAllLed2();

			setTimer(1, 100);
			setTimer(2, 25);
			setTimer(7,500);
		}

		if(Is_Button_Pressed(0))
		{
			pedestrian_flag = Pedestrian_GREEN;
			if(time1 < 5)
				setTimer(4, 1);

			setTimer(3, (timeRed + timeGreen) * 100);
		}
		break;

	case ManRed:
		if(isTimerUp(7) == 1)
		{
			status = RedGreen;

			setTimer(0, timeGreen * 100);
			setTimer(1, 1);

			time1 = timeRed;
			time2 = timeGreen;
		}

		if(isTimerUp(2) == 1)
		{
			setTimer(2, 25);
			toggleRed();
		}
		if(Is_Button_Pressed(2))
		{
			increase();
			setTimer(7,500);
		}

		if(Is_Button_Pressed(3))
		{
			balance(time1, timeYellow, timeGreen);
			setTimer(7,500);
		}

		if(Is_Button_Pressed(1))
		{
			status = ManAmber;

			time1 = timeYellow;
			time2 = 3;

			clearAllLed1();
			clearAllLed2();

			setTimer(2, 25);
			setTimer(7,500);
		}

		if(isTimerUp(1) == 1)
		{
			setTimer(1, 100);

			HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "\r\n!7SEG_LED1 - LED_RED_VALUE: %d#\r\n",time1), 500);
			HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "\r\n!7SEG_LED2 - MODE_RED:      %d#\r\n\n\n",time2), 500);
		}
		break;

	case ManAmber:
		if(isTimerUp(7) == 1)
		{
			status = RedGreen;
			setTimer(0, timeGreen * 100);
			setTimer(1, 1);

			time1 = timeRed;
			time2 = timeGreen;
		}

		if(isTimerUp(2) == 1)
		{
			setTimer(2, 25);
			toggleYellow();
		}

		if(Is_Button_Pressed(2))
		{
			increase();
			setTimer(7,500);
		}

		if(Is_Button_Pressed(3))
		{
			balance(timeRed, time1, timeGreen);
			setTimer(7,500);
		}

		if(Is_Button_Pressed(1))
		{
			status = ManGreen;

			time1 = timeGreen;
			time2 = 4;

			clearAllLed1();
			clearAllLed2();

			setTimer(2, 25);
			setTimer(7,500);
		}

		if(isTimerUp(1) == 1)
		{
			setTimer(1, 100);

			HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "\r\n!7SEG_LED1 - LED_AMBER_VALUE: %d#\r\n",time1), 500);
			HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "\r\n!7SEG_LED2 - MODE_AMBER:      %d#\r\n\n\n",time2), 500);
		}
		break;

	case ManGreen:
		if(isTimerUp(7) == 1)
		{
			status = RedGreen;

			setTimer(0, timeGreen * 100);
			setTimer(1, 1);

			time1 = timeRed;
			time2 = timeGreen;
		}

		if(isTimerUp(2) == 1)
		{
			setTimer(2, 25);
			toggleGreen();
		}

		if(Is_Button_Pressed(2))
		{
			increase();
			setTimer(7,500);
		}

		if(Is_Button_Pressed(3))
		{
			balance(timeRed, timeYellow, time1);
			setTimer(7,500);
		}

		if(Is_Button_Pressed(1))
		{
			status = RedGreen;

			setTimer(0, timeGreen * 100);
			setTimer(1, 1);

			time1 = timeRed;
			time2 = timeGreen;
		}

		if(isTimerUp(1) == 1)
		{
			setTimer(1, 100);

			HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "\r\n!7SEG_LED1 - LED_GREEN_VALUE: %d#\r\n",time1), 500);
			HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "\r\n!7SEG_LED2 - MODE_GREEN:      %d#\r\n\n\n",time2), 500);
		}
		break;

	default:
		break;
	}
}

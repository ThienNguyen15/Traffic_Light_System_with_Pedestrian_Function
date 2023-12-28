/*
 * button.c
 *
 *  Created on: Nov 27, 2023
 *      Author: Le Van Phuc			- 2152241
 *      		Nguyen Quang Thien	- 2152994
 */

#include "button.h"
#include "main.h"

// Aim to work with more than one buttons

#define N0_OF_BUTTONS 				       4

// Timer interrupt duration is 10ms, so to pass 1 second,
// Need to jump to the interrupt service routine 100 time

#define DURATION_FOR_AUTO_INCREASING	   100
#define BUTTON_IS_PRESSED                  GPIO_PIN_RESET
#define BUTTON_IS_RELEASED                 GPIO_PIN_SET

// The buffer that the final result is stored after
// Debouncing

static GPIO_PinState buttonBuffer[N0_OF_BUTTONS]={BUTTON_IS_RELEASED,BUTTON_IS_RELEASED,BUTTON_IS_RELEASED};

GPIO_TypeDef* buttonGPIO[N0_OF_BUTTONS]= {A0_GPIO_Port,A1_GPIO_Port,A2_GPIO_Port,A3_GPIO_Port };

static int buttonPin[N0_OF_BUTTONS]={A0_Pin, A1_Pin, A2_Pin, A3_Pin};

int buttonTimeOut[N0_OF_BUTTONS] = {0};

// Defining two buffers for debouncing

static GPIO_PinState debounceButtonBuffer1[N0_OF_BUTTONS];
static GPIO_PinState debounceButtonBuffer2[N0_OF_BUTTONS];
static GPIO_PinState debounceButtonBuffer3[N0_OF_BUTTONS];

// Defining a flag for a button pressed more than 1 second.
// Defining counter for automatically increasing the value
// After the button is pressed more than 1 second.

int buttonFlag[N0_OF_BUTTONS] = {0};
void Button_Reading(void)
{
	for(int i = 0; i < N0_OF_BUTTONS; i ++)
	{
		debounceButtonBuffer3[i] =debounceButtonBuffer2[i];
		debounceButtonBuffer2[i] =debounceButtonBuffer1[i];
		debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(buttonGPIO[i], buttonPin[i]);
		if(debounceButtonBuffer1[i] == debounceButtonBuffer2[i] && debounceButtonBuffer2[i] == debounceButtonBuffer3[i])
		{
			if(debounceButtonBuffer1[i] != buttonBuffer[i])
			{
				buttonBuffer[i] = debounceButtonBuffer1[i];
						if(buttonBuffer[i] == BUTTON_IS_PRESSED)
						{
							buttonFlag[i] = 1;
							buttonTimeOut[i] = DURATION_FOR_AUTO_INCREASING;
						}
			}
		}
		else
		{
			buttonTimeOut[i]--;
				if(buttonTimeOut[i] <= 0)
					buttonBuffer[i] = BUTTON_IS_RELEASED;
		}
	}
}

int Is_Button_Pressed(int index)
{
	if(index >= N0_OF_BUTTONS || index < 0)	return 0;

		if(buttonFlag[index] == 1)
		{
			buttonFlag[index] = 0;
			return 1;
		}
		return 0;
}

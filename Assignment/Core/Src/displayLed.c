/*
 * displayLed.c
 *
 *  Created on: Nov 27, 2023
 *      Author: Le Van Phuc			- 2152241
 *      		Nguyen Quang Thien	- 2152994
 */
#include "main.h"
#include "displayLed.h"

void clearAllLed1()
{
	HAL_GPIO_WritePin(D2_GPIO_Port, D2_Pin, RESET);
	HAL_GPIO_WritePin(D3_GPIO_Port, D3_Pin, RESET);
}

void clearAllLed2()
{
	HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, RESET);
	HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, RESET);
}
void displayRed1()
{
	HAL_GPIO_WritePin(D2_GPIO_Port, D2_Pin, SET);
	HAL_GPIO_WritePin(D3_GPIO_Port, D3_Pin, RESET);

}

void displayYellow1()
{
	HAL_GPIO_WritePin(D2_GPIO_Port, D2_Pin, SET);
	HAL_GPIO_WritePin(D3_GPIO_Port, D3_Pin, SET);
}

void displayGreen1()
{
	HAL_GPIO_WritePin(D2_GPIO_Port, D2_Pin, RESET);
	HAL_GPIO_WritePin(D3_GPIO_Port, D3_Pin, SET);
}

void displayRed2()
{
	HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, SET);
	HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, RESET);
}


void displayYellow2()
{
	HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, SET);
	HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, SET);
}

void displayGreen2()
{
	HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, RESET);
	HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, SET);
}

void toggleRed()
{	// Remember to clear all led before toggle
	HAL_GPIO_TogglePin(D2_GPIO_Port, D2_Pin);
	HAL_GPIO_TogglePin(D4_GPIO_Port, D4_Pin);
}

void toggleYellow()
{	// Remember to clear all led before toggle
	HAL_GPIO_TogglePin(D2_GPIO_Port, D2_Pin);
	HAL_GPIO_TogglePin(D3_GPIO_Port, D3_Pin);
	HAL_GPIO_TogglePin(D4_GPIO_Port, D4_Pin);
	HAL_GPIO_TogglePin(D5_GPIO_Port, D5_Pin);
}

void toggleGreen()
{	// Remember to clear all led before toggle
	HAL_GPIO_TogglePin(D3_GPIO_Port, D3_Pin);
	HAL_GPIO_TogglePin(D5_GPIO_Port, D5_Pin);
}

void clearPedestrian()
{
	HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, RESET);
	HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, RESET);
}

void displayPedestrianRed()
{
	HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, SET);
	HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, RESET);
}

void displayPedestrianYellow()
{
	HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, SET);
	HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, SET);
}

void displayPedestrianGreen()
{
	HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, RESET);
	HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, SET);
}

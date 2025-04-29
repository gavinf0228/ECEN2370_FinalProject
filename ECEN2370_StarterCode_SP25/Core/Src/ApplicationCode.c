/*
 * ApplicationCode.c
 *
 *  Created on: Dec 30, 2023 (updated 11/12/2024) Thanks Donavon! 
 *      Author: Xavion
 */

#include "ApplicationCode.h"
bool OnePlayer;
/* Static variables */
volatile bool drop;

extern void initialise_monitor_handles(void); 

#if COMPILE_TOUCH_FUNCTIONS == 1
static STMPE811_TouchData StaticTouchData;
#endif // COMPILE_TOUCH_FUNCTIONS

void ApplicationInit(void)
{
	initialise_monitor_handles(); // Allows printf functionality
    LTCD__Init();
    LTCD_Layer_Init(0);
    LCD_Clear(0,LCD_COLOR_WHITE);

    #if COMPILE_TOUCH_FUNCTIONS == 1
	InitializeLCDTouch();
	// This is the orientation for the board to be direclty up where the buttons are vertically above the screen
	// Top left would be low x value, high y value. Bottom right would be low x value, low y value.
	StaticTouchData.orientation = STMPE811_Orientation_Portrait_2;

	#endif // COMPILE_TOUCH_FUNCTIONS
}

void LCD_Visual_Demo(void)
{
	//  ScreenStart();
	// HAL_Delay(3000);
	// ScreenPlay();
	// visualDemo();
}

void ApplicationInitGameplay(){
	OnePlayer = ScreenStart();
	ScreenPlay();
	
	Player1 = true;

	InitGamePiece();

	//ScreenEnd();
}

void ApplicationInitPiece(){

	Player1 = true;
	InitGamePiece();
	// if (OnePlayer == false){
	// 	InitGamePiece();
	// } else {
	// 	initRNGPiece();
	// }
}

void ApplicationPieceMovement(){
	if (OnePlayer) {
		if (Player1){
			GamePieceMovement();
		} else {
			initRNGPiece();
		}
	} else {
		GamePieceMovement();
	}
	// if (OnePlayer == true){
	// 	initRNGPiece();
	// } else {
	// 	GamePieceMovement();
	// }
}

void ApplicationEndGame(){
	EndGame();
}
#if COMPILE_TOUCH_FUNCTIONS == 1
void LCD_Touch_Polling_Demo(void)
{
	LCD_Clear(0,LCD_COLOR_GREEN);
	while (1) {
		/* If touch pressed */
		if (returnTouchStateAndLocation(&StaticTouchData) == STMPE811_State_Pressed) {
			/* Touch valid */
			printf("\nX: %03d\nY: %03d\n", StaticTouchData.x, StaticTouchData.y);
			LCD_Clear(0, LCD_COLOR_RED);
		} else {
			/* Touch not pressed */
			printf("Not Pressed\n\n");
			LCD_Clear(0, LCD_COLOR_GREEN);
		}
	}
}

void EXTI0_IRQHandler(){

	EXTI_HandleTypeDef hexti;
	hexti.Line = EXTI_LINE_0;
	HAL_NVIC_DisableIRQ(EXTI0_IRQn);
	HAL_EXTI_ClearPending(&hexti, EXTI_TRIGGER_FALLING);
	DropGamePiece();
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}

#endif // COMPILE_TOUCH_FUNCTIONS


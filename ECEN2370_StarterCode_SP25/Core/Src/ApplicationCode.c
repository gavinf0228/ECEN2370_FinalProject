/*
 * ApplicationCode.c
 *
 *  Created on: Dec 30, 2023 (updated 11/12/2024) Thanks Donavon! 
 *      Author: Xavion
 */

#include "ApplicationCode.h"
bool OnePlayer; //bool that represents OnePlayer mode
/* Static variables */
volatile bool drop = false; // flag for the button interrupt that deals with dropping a piece

extern void initialise_monitor_handles(void); 

#if COMPILE_TOUCH_FUNCTIONS == 1
static STMPE811_TouchData StaticTouchData;
#endif // COMPILE_TOUCH_FUNCTIONS

void appDrop(){ //not used
	if (drop){
		drop = false;
		DropGamePiece();
	}
}
void ApplicationInit(void) // given to us. unchanged 
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

void LCD_Visual_Demo(void) // not used
{
	//  ScreenStart();
	// HAL_Delay(3000);
	// ScreenPlay();
	// visualDemo();
}

void ApplicationInitGameplay(){ // reset the game each time. init New game and set drop to false.
	ResetGame();
	NewGame();
	drop = false;
	
	OnePlayer = ScreenStart(); //OnePlayer flag is equal to startscreen which determines mode
	ScreenPlay(); //screen to play
	
	Player1 = true; //player 1 is yellow

	InitGamePiece();

	//ScreenEnd();
}

void ApplicationInitPiece(){ //piece is initialized

	Player1 = true; //player YELLOW
	InitGamePiece(); //game piece is drawn at top
	// if (OnePlayer == false){
	// 	InitGamePiece();
	// } else {
	// 	initRNGPiece();
	// }
}

void ApplicationPieceMovement(){
	if (drop){ //if drop occurs set back to false and call droppiece. this flag is used for button interrupt
		drop = false;
		DropGamePiece();
	}
	if (OnePlayer) { //if single player true. then human (Player1) will have movement. if not player1 (RNG) then it will do its thing
		if (Player1){
			GamePieceMovement();
		} else {
			initRNGPiece();
		}
	} else {
		GamePieceMovement(); // if 2 Player then you can move
	}
	// if (OnePlayer == true){
	// 	initRNGPiece();
	// } else {
	// 	GamePieceMovement();
	// }
}

void ApplicationEndGame(){ //ends the game
	EndGame();
}
#if COMPILE_TOUCH_FUNCTIONS == 1
void LCD_Touch_Polling_Demo(void) //unused
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

void EXTI0_IRQHandler(){ //button IRQ handler I took from previous lab. in MX GPIO added NVIC enabled for the EXTI0 IRQn for GPIOA. 

	EXTI_HandleTypeDef hexti;
	hexti.Line = EXTI_LINE_0;
	HAL_NVIC_DisableIRQ(EXTI0_IRQn);
	HAL_EXTI_ClearPending(&hexti, EXTI_TRIGGER_FALLING);
	drop = true;
	//DropGamePiece();
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}

#endif // COMPILE_TOUCH_FUNCTIONS


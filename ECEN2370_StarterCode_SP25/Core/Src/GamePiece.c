#include "GamePiece.h"
static uint16_t XPos;
static uint16_t YPos;
static uint16_t FillColor;
bool Player1;

void InitGamePiece(){
    if (Player 1 == true){
        FillColor = LCD_COLOR_YELLOW;
        XPos = LCD_PIXEL_WIDTH / 2;
        YPos = LCD_PIXEL_HEIGHT / 4;
        DrawGamePiece();
    } else{
        FillColor = LCD_COLOR_RED;
        XPos = LCD_PIXEL_WIDTH / 2;
        YPos = LCD_PIXEL_HEIGHT / 4;
        DrawGamePiece();
    }
}

void GamePieceLeft(){
    FillColor = LCD_COLOR_BLUE2;
    DrawGamePiece();

    XPos = XPos + MOVE_DISTANCE;
    FillColor = LCD_COLOR_YELLOW;
    DrawGamePiece();
}

void GamePieceRight(){
    FillColor = LCD_COLOR_BLUE2;
    DrawGamePiece();

    XPos = XPos - MOVE_DISTANCE;
    FillColor = LCD_COLOR_YELLOW;
    DrawGamePiece();
}

void GamePieceMovement(){
    STMPE811_TouchData touch;
    if (returnTouchStateAndLocation(&touch) == STMPE811_State_Pressed) {
        /* Touch valid */
        if (TM_STMPE811_TouchInRectangle(&touch, 0, 0, 120, 320)){
            GamePieceLeft();
            HAL_Delay(500);
        } else {
            GamePieceRight();
            HAL_Delay(500);
        }
    }
}

void DrawGamePiece(){
    LCD_Draw_Circle_Fill(XPos, YPos, 10, FillColor);
}
void DropGamePiece();
void IndicateTurn();
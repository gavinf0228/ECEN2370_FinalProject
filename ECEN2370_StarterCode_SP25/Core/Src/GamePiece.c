#include "GamePiece.h"
static BoardSettings currentplayer; //2d array to track winning data
static uint16_t XPos;   //keep track of moving piece left and right
static uint16_t YPos; //keep track of moving piece up and down (dropping)
static uint16_t FillColor; //changes color of piece
bool Player1; //for logic of changing colors

void InitGamePiece(){
    if (Player1 == true){
        currentplayer = YELLOW;
    } else {
        currentplayer = RED;
    }
    if (currentplayer == YELLOW) {
        FillColor = LCD_COLOR_YELLOW;
    } else{
        FillColor = LCD_COLOR_RED;
    }
    XPos = LCD_PIXEL_WIDTH / 2;
    YPos = LCD_PIXEL_HEIGHT / 4;
    DrawGamePiece();
}

void GamePieceLeft(){

    FillColor = LCD_COLOR_BLUE2;
    DrawGamePiece();

    XPos = XPos + MOVE_DISTANCE;
    if(currentplayer == YELLOW){
        FillColor = LCD_COLOR_YELLOW;
    } else if (currentplayer == RED){
        FillColor = LCD_COLOR_RED;
    }
    DrawGamePiece();
}

void GamePieceRight(){
    FillColor = LCD_COLOR_BLUE2;
    DrawGamePiece();

    XPos = XPos - MOVE_DISTANCE;
    if (currentplayer == YELLOW){
        FillColor = LCD_COLOR_YELLOW;
    } else if (currentplayer == RED){
        FillColor = LCD_COLOR_RED;
    }
    DrawGamePiece();
}

//combines all piece movements
void GamePieceMovement(){
    STMPE811_TouchData touch;
    if (returnTouchStateAndLocation(&touch) == STMPE811_State_Pressed) {
        /* Touch valid */
        if (TM_STMPE811_TouchInRectangle(&touch, 0, 0, 120, 200)){
            GamePieceLeft();
            HAL_Delay(500);
        } else if (TM_STMPE811_TouchInRectangle(&touch, 120, 0, 120, 200)){
            GamePieceRight();
            HAL_Delay(500);
        } else if (TM_STMPE811_TouchInRectangle(&touch, 0, 200, 240, 120)){
            DropGamePiece();
            HAL_Delay(500);
        }
    }
}

void DrawGamePiece(){
    LCD_Draw_Circle_Fill(XPos, YPos, 10, FillColor);
}

void DropGamePiece(){
    int pos = GetPieceData(XPos);
    for (int i = ROWS -1; i >= 0; i--){ //start bottom left and iterate up to determine if piece is there or not
        if (boardspots[i][pos] == CLEARED){
            boardspots[i][pos] = currentplayer;
            uint16_t x = CENTERCOLUMN + pos * PIECESPACING;
            uint16_t y = ROWSTART + i * PIECESPACING;

            if (currentplayer == YELLOW){
                LCD_Draw_Circle_Fill(x, y, PIECE_RADIUS, LCD_COLOR_YELLOW);
            } else {
                LCD_Draw_Circle_Fill(x, y, PIECE_RADIUS, LCD_COLOR_RED);
            }
            Player1 = !Player1; //switch to player two
            InitGamePiece();
            break;
        }
    }
}


// this gets the pixel position of the gamepiece. Used to track data for win
uint16_t GetPieceData(uint16_t piecepos){
    int pos = (piecepos - 15) / PIECESPACING;

    if (pos < 0){
        pos = 0;
    } else if (pos >= COLUMNS){
        pos = COLUMNS -1;
    }
    return pos;
}
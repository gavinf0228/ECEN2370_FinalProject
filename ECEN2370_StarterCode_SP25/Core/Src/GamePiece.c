#include "GamePiece.h"
static BoardSettings currentplayer; //2d array to track winning data
static uint16_t XPos;   //keep track of moving piece left and right
static uint16_t YPos; //keep track of moving piece up and down (dropping)
static uint16_t FillColor; //changes color of piece
bool Player1; //for logic of changing colors
bool endGame;


void InitGamePiece(){
    if (endGame == false){
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
}

void GamePieceLeft(){
    if (endGame == false){
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
}

void GamePieceRight(){
    if (endGame == false){
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
}

//combines all piece movements
void GamePieceMovement(){
    if (endGame == false){
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
    } EndGame();
}

void DrawGamePiece(){
    LCD_Draw_Circle_Fill(XPos, YPos, 10, FillColor);
}

void DropGamePiece(){
    if (endGame == false){
        int pos = GetPieceData(XPos);
        LCD_Draw_Circle_Fill(XPos, YPos, PIECE_RADIUS, LCD_COLOR_BLUE2); // clears piece when its dropped
        for (int i = ROWS -1; i >= 0; i--){ //start bottom left and iterate up to determine if piece is there or not
            if (boardspots[i][pos] == CLEARED){ //if spot is empty then first empty spot from bottom is where new piece placed
                boardspots[i][pos] = currentplayer;
                uint16_t x = CENTERCOLUMN + pos * PIECESPACING; 
                uint16_t y = ROWSTART + i * PIECESPACING;

                if (currentplayer == YELLOW){
                    LCD_Draw_Circle_Fill(x, y, PIECE_RADIUS, LCD_COLOR_YELLOW);
                } else {
                    LCD_Draw_Circle_Fill(x, y, PIECE_RADIUS, LCD_COLOR_RED);
                }
                CheckWin();
                Player1 = !Player1; //switch to player two
                InitGamePiece();
                break;
            }
        }
    }
}


// this gets the pixel position of the gamepiece. Used to track data for win
uint16_t GetPieceData(uint16_t piecepos){
    int pos = (piecepos - CENTERPIECE_IFOFF) / PIECESPACING;

    if (pos < 0){
        pos = 0;
    } else if (pos >= COLUMNS){
        pos = COLUMNS -1;
    }
    return pos;
}

// semi brute force way of checking for wins
bool CheckWin() {
    if (currentplayer == YELLOW) {
        for (int i = 0; i < ROWS; i++) { //iterate through rows
            for (int j = 0; j < COLUMNS; j++) { //iterate through columns
                if(i+3 < ROWS){ // checks for below placed piece
                    if(boardspots[i][j] == 1 &&
                    boardspots[i+1][j] == 1 &&
                    boardspots[i+2][j] == 1 &&
                    boardspots[i+3][j] == 1){
                        endGame = true;
                    }
                } if (i-3 >= 0){ // checks above placed piece
                    if(boardspots[i][j] == 1 &&
                    boardspots[i-1][j] == 1 &&
                    boardspots[i-2][j] == 1 &&
                    boardspots[i-3][j] == 1){
                        endGame = true;
                    }
                } if (j +3 < COLUMNS) { //checks right of placed piece
                    if (boardspots[i][j] == 1 &&
                    boardspots[i][j+1] == 1 &&
                    boardspots[i][j+2] == 1 &&
                    boardspots[i][j+3] == 1){
                        endGame = true;
                    }
                } if (j -3 >= 0) { // checks left of placed piece
                    if (boardspots[i][j] == 1 &&
                    boardspots[i][j-1] == 1 &&
                    boardspots[i][j-2] == 1 &&
                    boardspots[i][j-3] == 1){
                        endGame = true;
                    }
                } if ((i + 3 < ROWS) && (j + 3 < COLUMNS)){ //checks diagonally down right 
                    if (boardspots[i][j] == 1 &&
                    boardspots[i+1][j+1] == 1 &&
                    boardspots[i+2][j+2] == 1 &&
                    boardspots[i+3][j+3] == 1){
                        endGame = true;
                    }
                } if ((i -3 >= 0) && (j+3 < COLUMNS)){ // checks diagonally up right
                    if (boardspots[i][j] == 1 &&
                    boardspots[i-1][j+1] == 1 &&
                    boardspots[i-2][j+2] == 1 &&
                    boardspots[i-3][j+3] == 1){
                        endGame = true;
                    }
                }
            }
        }
    } else if(currentplayer == RED){ //same code as if current player is yellow. just for red player now
        for (int k = 0; k < ROWS; k++) {
            for (int l = 0; l < COLUMNS; l++) {
                if(k+3 < ROWS){
                    if(boardspots[k][l] == 2 &&
                    boardspots[k+1][l] == 2 &&
                    boardspots[k+2][l] == 2 &&
                    boardspots[k+3][l] == 2){
                        endGame = true;
                    }
                } if (k-3 >= 0){
                    if(boardspots[k][l] == 2 &&
                    boardspots[k-1][l] == 2 &&
                    boardspots[k-2][l] == 2 &&
                    boardspots[k-3][l] == 2){
                        endGame = true;
                    }
                }if (l +3 < COLUMNS) {
                    if (boardspots[k][l] == 2 &&
                    boardspots[k][l+1] == 2 &&
                    boardspots[k][l+2] == 2 &&
                    boardspots[k][l+3] == 2){
                        endGame = true;
                    }
                } if (l -3 >= 0) {
                    if (boardspots[k][l] == 2 &&
                    boardspots[k][l-1] == 2 &&
                    boardspots[k][l-2] == 2 &&
                    boardspots[k][l-3] == 2){
                        endGame = true;
                    }
                } if ((k + 3 < ROWS) && (l + 3 < COLUMNS)){
                    if (boardspots[k][l] == 2 &&
                    boardspots[k][l+1] == 2 &&
                    boardspots[k][l+2] == 2 &&
                    boardspots[k][l+3] == 2){
                        endGame = true;
                    } 
                } if ((k + 3 < ROWS) && (l + 3 < COLUMNS)){ //checks diagonally down right 
                    if (boardspots[k][l] == 2 &&
                    boardspots[k+1][l+1] == 2 &&
                    boardspots[k+2][l+2] == 2 &&
                    boardspots[k+3][l+3] == 2){
                        endGame = true;
                    }
                } if ((k -3 >= 0) && (l+3 < COLUMNS)){
                    if (boardspots[k][l] == 2 &&
                    boardspots[k-1][l+1] == 2 &&
                    boardspots[k-2][l+2] == 2 &&
                    boardspots[k-3][l+3] == 2){
                        endGame = true;
                    }
                }
            }
        }
    } return endGame;
}

void EndGame(){
    if (CheckWin() == true){
        ScreenEnd();
    }
}

bool GetEndgame(){
    return endGame;
}

void setEndgame(bool newval){
    endGame = newval;
}

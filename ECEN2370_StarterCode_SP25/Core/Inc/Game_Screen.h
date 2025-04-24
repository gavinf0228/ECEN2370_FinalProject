#include "LCD_Driver.h"
#include <stdbool.h>

#define ROWS 6
#define COLUMNS 7
#define PLAYER_1 1
#define PLAYER_2 2
#define GAMEON  1
#define GAMEOFF 0

typedef enum {
    CLEARED,
    YELLOW,
    RED,
}Board_TypeDef_t;

Board_TypeDef_t boardspots[ROWS][COLUMNS];

void GameDrawBoard();
void ScreenStart();
void ScreenPlay();
void ScreenEnd();
void DropGamePiece();




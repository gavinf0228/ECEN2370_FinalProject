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
}BoardSettings;

extern BoardSettings boardspots[ROWS][COLUMNS];

void NewGame();
void Drawboard();
void GameBoardGrid();
void ScreenStart();
void ScreenPlay();
void ScreenEnd();
void DropGamePiece();




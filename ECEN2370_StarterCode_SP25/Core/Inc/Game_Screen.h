#include "LCD_Driver.h"
#include "Timer_Driver.h"
#include <stdbool.h>
#define ROWS 6
#define COLUMNS 7
#define BOARD_LEFT  18
#define BOARD_RIGHT (30 + (COLUMNS - 1) * 30 + 12)
#define BOARD_TOP   108
#define BOARD_BOTTOM    (120 + (ROWS - 1) * 30 + 12)

extern uint16_t RedScore; // used in multiple files. tracks Redscore
extern uint16_t YellowScore; // tracks Yellow score

//enum for clearing and keeping track of color turn and such
typedef enum {
    CLEARED,
    YELLOW,
    RED,
}BoardSettings;

extern BoardSettings boardspots[ROWS][COLUMNS]; //data for the board


void NewGame();
void Drawboard();
void GameBoardGrid();
bool ScreenStart();
void ScreenPlay();
void ScreenEnd();
void DropGamePiece();
void ScoreBoard(uint16_t red, uint16_t yellow);
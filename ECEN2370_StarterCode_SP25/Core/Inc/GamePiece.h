#include "Game_Screen.h"
#include "RNG_Driver.h"
#define MOVE_DISTANCE   30
#define PIECE_RADIUS    10
#define PIECESPACING   MOVE_DISTANCE
#define CENTERCOLUMN    30
#define ROWSTART        120
#define CENTERPIECE_IFOFF   15
#define LEFT_COLUMN     30

extern bool Player1;

extern BoardSettings currentplayer;

void InitGamePiece();
void GamePieceLeft();
void GamePieceRight();
void GamePieceMovement();
void DrawGamePiece();
void DropGamePiece();
uint16_t GetPieceData(uint16_t piecepos);
bool CheckWin();
void EndGame();
bool GetEndgame();
void setEndgame(bool newval);
void initRNGPiece();


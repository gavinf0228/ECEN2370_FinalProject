#include "Game_Screen.h"
BoardSettings boardspots[ROWS][COLUMNS];
uint16_t RedScore =0;
uint16_t YellowScore =0;
bool gamemode;  //gamemode = true is single player. false - 2 player

void NewGame(){
    StartTimer();
    for (int r = 0; r < ROWS; r++){
        for (int c = 0; c < COLUMNS; c++) {
            boardspots[r][c] = CLEARED;
        }
    }
}

void Drawboard(){
    for (int r = 0; r < ROWS; r++){
        for (int c = 0; c < COLUMNS; c++){
            uint16_t x = 30 + c * 30;
            uint16_t y = 120 + r * 30;
            uint16_t color;
            switch (boardspots[r][c]){
                case CLEARED: color = LCD_COLOR_WHITE;
                    break;
                case YELLOW: color = LCD_COLOR_YELLOW;
                    break;
                case RED: color = LCD_COLOR_RED;
                    break;
            }
            LCD_Draw_Circle_Fill(x, y, 10, color);
        }
    }
}
void GameBoardGrid(){

    uint16_t board_left = 30 - 12;
    uint16_t board_right = 30 + (COLUMNS - 1) * 30 + 12;
    uint16_t board_top = 120 - 12;
    uint16_t board_bottom = 120 + (ROWS - 1) * 30 + 12;

      // draw top and bottom borders as horizontal lines using vertical line of height 1
    for (uint16_t x = board_left; x <= board_right; ++x) {
          LCD_Draw_Vertical_Line(x, board_top, 1, LCD_COLOR_BLACK);    // top border
          LCD_Draw_Vertical_Line(x, board_bottom, 1, LCD_COLOR_BLACK); // bottom border
      }

      // draw left and right borders
      LCD_Draw_Vertical_Line(board_left, board_top, board_bottom - board_top + 1, LCD_COLOR_BLACK);  // left border
      LCD_Draw_Vertical_Line(board_right, board_top, board_bottom - board_top + 1, LCD_COLOR_BLACK);
      for (int c = 1; c < COLUMNS; ++c) {
              uint16_t x = 30 + c * 30 - 15; // halfway between circles
              LCD_Draw_Vertical_Line(x, board_top, board_bottom - board_top + 1, LCD_COLOR_BLACK);
          }

          // Draw horizontal dividers between rows
          for (int r = 1; r < ROWS; ++r) {
              uint16_t y = 120 + r * 30 - 15; // halfway between circles
              for (uint16_t x = board_left; x <= board_right; ++x) {
                  LCD_Draw_Vertical_Line(x, y, 1, LCD_COLOR_BLACK);
              }
          }
}


void ScreenStart(){

    STMPE811_TouchData touch;

    LCD_Clear(0, LCD_COLOR_YELLOW);

    LCD_SetFont(&Font16x24);
    LCD_SetTextColor(LCD_COLOR_BLACK);
    
    LCD_DisplayChar(56, 20, 'C'); HAL_Delay(200); LCD_DisplayChar(72, 20, 'O'); HAL_Delay(200); LCD_DisplayChar(88, 20, 'N'); HAL_Delay(200); 
    LCD_DisplayChar(104, 20, 'N'); HAL_Delay(200); LCD_DisplayChar(120, 20, 'E'); HAL_Delay(200); LCD_DisplayChar(136, 20, 'C');
    HAL_Delay(200); LCD_DisplayChar(152, 20, 'T'); HAL_Delay(200); LCD_DisplayChar(168, 20, '4');

    LCD_SetFont(&Font16x24);
    LCD_DisplayChar(56, 90, '1'); LCD_DisplayChar(72, 90, '-'); LCD_DisplayChar(88, 90, 'P');
    LCD_DisplayChar(104, 90, 'L');LCD_DisplayChar(120, 90, 'A');LCD_DisplayChar(136, 90, 'Y');
    LCD_DisplayChar(152, 90, 'E'); LCD_DisplayChar(168, 90, 'R');

    LCD_DisplayChar(56, 180, '2'); LCD_DisplayChar(72, 180, '-');LCD_DisplayChar(88, 180, 'P');
    LCD_DisplayChar(104, 180, 'L');LCD_DisplayChar(120, 180, 'A');LCD_DisplayChar(136, 180, 'Y');
    LCD_DisplayChar(152, 180, 'E');LCD_DisplayChar(168, 180, 'R');
    
    LCD_Draw_Circle_Fill(120, 140, 30, LCD_COLOR_RED);
    LCD_Draw_Circle_Fill(120, 230, 30, LCD_COLOR_BLUE2);
    
    while (1) {
		/* If touch pressed */
		if (returnTouchStateAndLocation(&touch) == STMPE811_State_Pressed) {
			/* Touch valid */
            if (TM_STMPE811_TouchInRectangle(&touch, 120-30, 140-30, 60, 60)){
                // gamemode = true;
                ScreenPlay();
                break;
            // } else if (TM_STMPE811_TouchInRectangle(&touch, 120-30, 230 - 30, 60,60)){
            //     gamemode false;
            //     break
            }
        }
    } //return gamemode; 
}



void ScreenPlay(){
    LCD_Clear(0, LCD_COLOR_BLUE2);
    LCD_SetFont(&Font12x12);
    LCD_SetTextColor(LCD_COLOR_BLACK);

    LCD_DisplayChar(10, 10, 'P'); LCD_DisplayChar(26, 10, 'L'); LCD_DisplayChar(42, 10, 'A'); LCD_DisplayChar(58, 10, 'Y');
    LCD_DisplayChar(74, 10, 'E'); LCD_DisplayChar(90, 10, 'R');LCD_DisplayChar(106, 10, ' '); LCD_DisplayChar(114, 10, '1');
    LCD_Draw_Circle_Fill(130, 15, 5, LCD_COLOR_RED);

    LCD_DisplayChar(10, 40, 'P'); LCD_DisplayChar(26, 40, 'L');  LCD_DisplayChar(42, 40, 'A'); LCD_DisplayChar(58, 40, 'Y');
    LCD_DisplayChar(74, 40, 'E'); LCD_DisplayChar(90, 40, 'R');  LCD_DisplayChar(106, 40, ' '); LCD_DisplayChar(114, 40, '2');
    LCD_Draw_Circle_Fill(130, 45, 5, LCD_COLOR_YELLOW);

    NewGame();
    Drawboard();
    GameBoardGrid();
}

void ScreenEnd(){
    STMPE811_TouchData touch;
    StopTimer();

    uint32_t time = GetTimer();
    uint32_t hundreds = (time / 100) % 10;
    uint32_t tens = (time / 10) % 10;
    uint32_t ones = (time /1) % 10;


    
    LCD_Clear(0, LCD_COLOR_GREEN);

    LCD_SetFont(&Font12x12);
    LCD_SetTextColor(LCD_COLOR_BLACK);

    LCD_DisplayChar(10, 10, 'T'); LCD_DisplayChar(26, 10, 'I'); LCD_DisplayChar(42, 10, 'M'); LCD_DisplayChar(58, 10, 'E'); LCD_DisplayChar(74, 10, ':');
    LCD_DisplayChar(74 + 16, 10, hundreds + '0');
    LCD_DisplayChar(74 + 16 + 16, 10, tens + '0');
    LCD_DisplayChar(74 + 16 + 16 + 16, 10, ones + '0');

    LCD_DisplayChar(10, 25, 'R'); LCD_DisplayChar(26, 25, 'E'); LCD_DisplayChar(42, 25, 'D'); LCD_DisplayChar(58, 25, ':'); 
    LCD_SetTextColor(LCD_COLOR_RED);
    LCD_DisplayChar(58 +16, 25, RedScore +'0');
    
    LCD_SetTextColor(LCD_COLOR_BLACK);
    LCD_DisplayChar(10, 40, 'Y'); LCD_DisplayChar(26, 40, 'E'); LCD_DisplayChar(42, 40, 'L'); LCD_DisplayChar(58, 40, 'L'); LCD_DisplayChar(74, 40, 'O');  
    LCD_DisplayChar(74+16, 40, 'W');  LCD_DisplayChar(74+16+16, 40, ':'); 
    LCD_SetTextColor(LCD_COLOR_YELLOW);
    LCD_DisplayChar(74+16+16+16, 40, YellowScore + '0');
    
    LCD_SetTextColor(LCD_COLOR_BLACK);
    LCD_DisplayChar(56+30, 100, 'W'); LCD_DisplayChar(72+30, 100, 'I'); LCD_DisplayChar(88+30, 100, 'N'); LCD_DisplayChar(88+16+30, 100, 'S');
    LCD_DisplayChar(88+16+30+16,100, '!'); 

    

    LCD_SetFont(&Font16x24);
    
    LCD_DisplayChar(56+30, 180, 'P'); LCD_DisplayChar(72+30, 180, 'L'); LCD_DisplayChar(88+30, 180, 'A');
    LCD_DisplayChar(104+30, 180, 'Y');LCD_DisplayChar(56-8+30, 205, 'A');LCD_DisplayChar(56-8+16+30, 205, 'G');
    LCD_DisplayChar(56-8+16+16+30, 205, 'A'); LCD_DisplayChar(56-8+16+16+16+30, 205, 'I'); LCD_DisplayChar(56-8+16+16+16+16+30, 205, 'N');
    
    LCD_Draw_Circle_Fill(120, 250,20,LCD_COLOR_BLUE2);
    while (1) {
		/* If touch pressed */
		if (returnTouchStateAndLocation(&touch) == STMPE811_State_Pressed) {
			/* Touch valid */
            if (TM_STMPE811_TouchInRectangle(&touch, 120-20, 250-20, 40, 40)){
                HAL_Delay(500);
                ScreenStart();
                break;
            }
        } 
    } 
}


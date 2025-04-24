#include "Game_Screen.h"

void GameDrawBoard(){

    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLUMNS; ++c) {
            uint16_t x = 30 + c *30;
            uint16_t y = 120 + r * 30;
            LCD_Draw_Circle_Fill(x, y, 10, LCD_COLOR_WHITE);
        }
    }
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
    
    LCD_DisplayChar(56, 20, 'C'); LCD_DisplayChar(72, 20, 'O');LCD_DisplayChar(88, 20, 'N');
    LCD_DisplayChar(104, 20, 'N');LCD_DisplayChar(120, 20, 'E');LCD_DisplayChar(136, 20, 'C');
    LCD_DisplayChar(152, 20, 'T');LCD_DisplayChar(168, 20, '4');

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
            if (TM_STMPE811_TouchInRectangle(&touch, 120-30, 140-30, 60, 60) || TM_STMPE811_TouchInRectangle(&touch, 120-30, 230 - 30, 60,60)){
                HAL_Delay(500);
                ScreenPlay();
                break;
            }
        }
    }
}


void ScreenPlay(){
    LCD_Clear(0, LCD_COLOR_BLUE2);
    LCD_SetFont(&Font12x12);
    LCD_SetTextColor(LCD_COLOR_BLACK);

    LCD_DisplayChar(10, 10, 'P'); LCD_DisplayChar(26, 10, 'L'); LCD_DisplayChar(42, 10, 'A'); LCD_DisplayChar(58, 10, 'Y');
    LCD_DisplayChar(74, 10, 'E'); LCD_DisplayChar(90, 10, 'R');LCD_DisplayChar(106, 10, ' '); LCD_DisplayChar(122, 10, '1');

    LCD_DisplayChar(10, 40, 'P'); LCD_DisplayChar(26, 40, 'L');  LCD_DisplayChar(42, 40, 'A'); LCD_DisplayChar(58, 40, 'Y');
    LCD_DisplayChar(74, 40, 'E'); LCD_DisplayChar(90, 40, 'R');  LCD_DisplayChar(106, 40, ' '); LCD_DisplayChar(122, 40, '2');

    // LCD_Draw_Circle_Fill()

    GameDrawBoard();
}

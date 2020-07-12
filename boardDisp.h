#ifndef  _BOARD_DISP_H_
#define  _BOARD_DISP_H_

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#include "board.h"

int startDisp();
void stopDisp();

void drawBoard(board_t board);
void drawOver(const char* str);
void drawUnder(const char* str);


#endif //_BOARD_DISP_H_
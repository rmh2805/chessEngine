#ifndef  _CHESS_DISP_H_
#define  _CHESS_DISP_H_

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#include "chessConst.h"
#include "chessBoard.h"

int startDisp (int *numRows, int* numCols);

int stopDisp ();

void drawBoard(board_t board);

void drawTurn(const char * turn);

void drawPrompt();

#endif //_CHESS_DISP_H_

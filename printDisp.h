#ifndef  _PRINT_DISP_H_
#define  _PRINT_DISP_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "board.h"
#include "chessConst.h"

int printInit(board_t board);
void printStop();

void printHelpPrompt(const char * msg);
void printBoard(board_t board);
void printMsg(const char * msg);
void printScore(const char * score);

void printGetStr(char * buf, size_t bufSize);

#endif //_PRINT_DISP_H_

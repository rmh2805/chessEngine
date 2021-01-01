#ifndef  _PRINT_DISP_H_
#define  _PRINT_DISP_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "board.h"
#include "chessConst.h"

int printInit();

void printStop();

void printBoard(board_t board);

void printGetStr(char * buf, size_t bufSize);

void printHelpPrompt();

#endif //_PRINT_DISP_H_

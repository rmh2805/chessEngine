#ifndef  _CURESE_DISP_H_
#define  _CURSES_DISP_H_

#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>

#include "chessConst.h"
#include "board.h"

int cursesInit(board_t board);
void cursesClose();

void cursesDispHelp(const char * msg);
void cursesDispBoard(board_t board);
void cursesDispMsg(const char * msg);
void cursesDispScore(const char * score);

void cursesGetStr(char * buf, size_t bufSize);

#endif //_CURSES_DIAP_H_

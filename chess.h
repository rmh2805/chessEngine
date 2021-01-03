#ifndef  _CHESS_H_
#define  _CHESS_H_

#include <stdlib.h>
#include <stdbool.h>

#include "board.h"
#include "chessConst.h"

void setBoard(board_t board);

char pieceDispFromVal(char val);
char pieceValFromDisp(char disp);

#endif //_CHESS_H_

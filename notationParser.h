#ifndef  _NOTATION_PARSER_H_
#define  _NOTATION_PARSER_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "chessConst.h"
#include "piece.h"

#include "chessBoard.h"

char* notationToMove (board_t board, const char * move);



#endif //_NOTATION_PARSER_H_

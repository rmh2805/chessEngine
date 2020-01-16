#ifndef  _NOTATION_PARSER_H_
#define  _NOTATION_PARSER_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "chessConst.h"
#include "piece.h"

#include "chessBoard.h"

extern const char standardMoveFlag;
extern const char enPassentFlag;
extern const char queenCastleFlag;
extern const char kingCastleFlag;
extern const char checkFlag;
extern const char mateFlag;

char* notationToMove (board_t board, const char * move, bool whiteMove);



#endif //_NOTATION_PARSER_H_

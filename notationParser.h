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

/*
 *  Standard: ['n', Source Rank, Source File, Dest Rank, Dest File]
 *  En passent: ['e', Source Rank, Source File, Dest Rank, Dest File]
 *  Queen-side castle: ['q']
 *  King-side castle: ['k']
 *  Check: ['c']
 *  Mate: ['m']
 *  Definitely Illegal: NULL
 *  All legal returns (except standard) must have further checks for legality, as they all have historical state dependancies
 *  All legal returns must be freed by caller
 */
char* notationToMove (board_t board, const char * move, bool whiteMove);



#endif //_NOTATION_PARSER_H_

#ifndef  _PIECE_MOVE_H_
#define  _PIECE_MOVE_H_

#include <stdlib.h>
#include <stdbool.h>

#include "board.h"
#include "chessConst.h"

typedef struct gameStats_s * gameStats_t;

gameStats_t makeGameStats();
void delGameStats(gameStats_t stats);

bool moveLegal(gameStats_t stats, board_t board, size_t startRow, size_t startCol, size_t endRow, size_t endCol);
bool makeMove(gameStats_t stats, board_t board, size_t startRow, size_t startCol, size_t endRow, size_t endCol);


#endif //_PIECE_MOVE_H_

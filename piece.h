#ifndef  _PIECE_H_
#define  _PIECE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "chessboard.h"

#define kPawnFlag 'P'
#define kKnightFlag 'N'
#define kBishopFlag 'B'
#define kRookFlag 'R'
#define kQueenFlag 'Q'
#define kKingFlag 'K'


extern const char kPieceTypes[];
extern const int kNumPieceTypes;

bool isPiece (char piece);

bool canMove (board_t board, char srcFile, int srcRank, char destFile, int destRank);

#endif //_PIECE_H_

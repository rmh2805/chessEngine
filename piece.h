#ifndef  _PIECE_H_
#define  _PIECE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "chessBoard.h"

#define kPawnFlag 'P'
#define kKnightFlag 'N'
#define kBishopFlag 'B'
#define kRookFlag 'R'
#define kQueenFlag 'Q'
#define kKingFlag 'K'


extern const char kPieceTypes[];
extern const int kNumPieceTypes;

bool isPiece (char piece);
bool colorMatch (board_t board, int rank, char file, bool isWhite);

bool canMove (board_t board, int srcRank, char srcFile, int destRank, char destFile);

#endif //_PIECE_H_

#ifndef  _CHESS_BOARD_H_
#define  _CHESS_BOARD_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "chessConst.h"

struct board_s {
    char ** data;
};

typedef struct board_s* board_t;

void deleteBoard (board_t board);
board_t makeBoard ();

bool pieceWhite(board_t board, int rank, char file);
bool pieceBlack(board_t board, int rank, char file);
bool cellEmpty(board_t board, int rank, char file);
char pieceType (board_t board, int rank, char file);

bool isRank(int rank);
bool isFile(char file);

void setPiece(board_t board, bool isWhite, char type, int rank, char file);
void clearCell(board_t board, int rank, char file);
void movePiece(board_t board, int srcRank, char srcFile, int destRank, char destFile);

#endif //_CHESS_BOARD_H_

#ifndef  _BOARD_H_
#define  _BOARD_H_

#include <stdlib.h>
#include <stdbool.h>

#include "chessConst.h"

#define kBoardCols 8
#define kBoardRows 8

typedef struct board_s * board_t;

//====================================<Allocation and Freeing>====================================//
board_t makeBoard();
void delBoard(board_t board);

//=====================================<Getters and Setters>======================================//
size_t getNRows(board_t board);

size_t getNCols(board_t board);

char getCell(board_t board, size_t row, size_t col);

void clearCell(board_t board, size_t row, size_t col);

void setCell(board_t board, size_t row, size_t col, char piece, bool isWhite);

//===========================================<Helpers>============================================//
size_t rowFromFile(char file);
size_t colFromRank(char rank);

#endif //_BOARD_H_

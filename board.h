#ifndef  _BOARD_H_
#define  _BOARD_H_

#include <stdlib.h>

#define kBoardCols 8
#define kBoardRows 8

typedef struct board_s * board_t;

//====================================<Allocation and Freeing>====================================//
board_t makeBoard();
void delBoard(board_t board);

//=====================================<Getters and Setters>======================================//
char getCell(board_t board, unsigned int row, unsigned int col);
void setCell(board_t board, unsigned int row, unsigned int col, char piece);

//===========================================<Helpers>============================================//
unsigned int rowFromFile(char file);
unsigned int colFromRank(char rank);

#endif //_BOARD_H_
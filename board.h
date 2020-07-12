#ifndef  _BOARD_H_
#define  _BOARD_H_

#include <stdlib.h>

#define kBoardFiles 8
#define kBoardRanks 8

typedef struct board_s * board_t;

//====================================<Allocation and Freeing>====================================//
board_t makeBoard();
void delBoard(board_t board);

//=====================================<Getters and Setters>======================================//
char getCell(board_t board, unsigned int rank, unsigned int file);
void setCell(board_t board, unsigned int rank, unsigned int file, char piece);

#endif //_BOARD_H_
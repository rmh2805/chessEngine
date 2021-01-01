#include "board.h"

struct board_s {
    size_t nRows;
    size_t nCols;
    char** data;
};

//====================================<Allocation and Freeing>====================================//
board_t makeBoard() {
    board_t board = malloc(sizeof(struct board_s));
    if(board == NULL) {
        return NULL;
    }
    
    board->data = calloc(kBoardRows, sizeof(char*));
    if(board->data == NULL) {
        delBoard(board);
        return NULL;
    }

    for(int i = 0; i < kBoardRows; i++) {
        board->data[i] = calloc(kBoardCols, sizeof(char));
        if(board->data[i] == NULL) {
            delBoard(board);
            return NULL;
        }
    }
    
    board->nRows = kBoardRows;
    board->nCols = kBoardCols;

    return board;
}


void delBoard(board_t board) {
    if(board == NULL) {
        return;
    }

    if(board->data != NULL) {
        for(size_t i = 0; i < board->nRows; i++) {
            if(board->data[i] != NULL) {
                free(board->data[i]);
            }
        }
        free(board->data);
    }

    free(board);
}

//=====================================<Getters and Setters>======================================//
size_t getNRows(board_t board) {
    return (board == NULL) ? 0 : board->nRows;
}

size_t getNCols(board_t board) {
    return (board == NULL) ? 0 : board->nCols;
}

char getCell(board_t board, size_t row, size_t col) {
    if(board == NULL || row >= board->nRows || col >= board->nCols) {
        return '\0';
    }

    return board->data[row][col];
}

void clearCell(board_t board, size_t row, size_t col) {
    if(board == NULL || row >= board->nRows || col >= board->nCols) {
        return;
    }

    board->data[row][col] = kEmptyCell;
}

void setCell(board_t board, size_t row, size_t col, char val, bool isWhite) {
    if(board == NULL || row >= board->nRows || col >= board->nCols) {
        return;
    }

    val = val & kColorMask;
    if(isWhite)
        val = val | kWhiteFlag;

    board->data[row][col] = val;
}

//===========================================<Helpers>============================================//
size_t rowFromFile(char file) {
    if(file < '0') {
        return 0;
    }

    size_t row = file - '0';
    if(row > kBoardRows) {
        return 0;
    }

    return row;

}

size_t colFromRank(char rank) {
    if(rank >= 'a' && rank <= 'a' + kBoardCols) {
        rank = rank - 'a' + 'A';
    }

    if(rank < 'A' || rank > 'A' + kBoardCols) {
        return 0;
    }
    
    size_t col = rank - 'A';
    return col;

}


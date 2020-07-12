#include "board.h"

struct board_s {
    char** data;
};

//====================================<Allocation and Freeing>====================================//
board_t makeBoard() {
    board_t board = malloc(sizeof(struct board_s));
    if(board == NULL) {
        return;
    }
    
    board->data = calloc(kBoardRows, sizeof(char*));
    if(board->data == NULL) {
        delBoard(board);
        return;
    }

    for(int i = 0; i < kBoardRows; i++) {
        board->data[i] = calloc(kBoardCols, sizeof(char));
        if(board->data[i] == NULL) {
            delBoard(board);
            return;
        }
    }

    return board;
}


void delBoard(board_t board) {
    if(board == NULL) {
        return;
    }

    if(board->data != NULL) {
        for(int i = 0; i < kBoardRows; i++) {
            if(board->data[i] != NULL) {
                free(board->data[i]);
            }
        }
        free(board->data);
    }

    free(board);
}

//=====================================<Getters and Setters>======================================//
char getCell(board_t board, unsigned int row, unsigned int col) {
    if(board == NULL || row >= kBoardRows || col >= kBoardCols) {
        return '\0';
    }

    return board->data[row][col];
}

void setCell(board_t board, unsigned int row, unsigned int col, char piece) {
    if(board == NULL || row >= kBoardRows || col >= kBoardCols) {
        return;
    }

    board->data[row][col] = piece;
}

//===========================================<Helpers>============================================//
unsigned int rowFromFile(char file) {
    if(file < '0') {
        return 0;
    }

    unsigned int row = file - '0';
    if(row > kBoardRows) {
        return 0;
    }

    return row;

}

unsigned int colFromRank(char rank) {
    if(rank >= 'a' && rank <= 'a' + kBoardCols) {
        rank = rank - 'a' + 'A';
    }

    if(rank < 'A' || rank > 'A' + kBoardCols) {
        return 0;
    }
    
    unsigned int col = rank - 'A';
    return col;

}


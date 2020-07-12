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
    
    board->data = calloc(kBoardRanks, sizeof(char*));
    if(board->data == NULL) {
        delBoard(board);
        return;
    }

    for(int i = 0; i < kBoardRanks; i++) {
        board->data[i] = calloc(kBoardFiles, sizeof(char));
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
        for(int i = 0; i < kBoardRanks; i++) {
            if(board->data[i] != NULL) {
                free(board->data[i]);
            }
        }
        free(board->data);
    }

    free(board);
}

//=====================================<Getters and Setters>======================================//
char getCell(board_t board, unsigned int rank, unsigned int file) {
    if(board == NULL) {
        return '\0';
    }

    return board->data[rank][file];
}

void setCell(board_t board, unsigned int rank, unsigned int file, char piece) {
    if(board == NULL) {
        return;
    }

    board->data[rank][file] = piece;
}

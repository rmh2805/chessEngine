#include <stdlib.h>
#include <stdio.h>

#include "board.h"

void printBoard(board_t board) {
    if(board == NULL) {
        return;
    }

    printf("+");
    for(unsigned int col = 0; col < kBoardCols; col++) {
        printf("-");
    }
    printf("+\n");

    for (unsigned int row = 0; row < kBoardRows; row++) {
        printf("|");
        for (unsigned int col = 0; col < kBoardCols; col++) {
            char cell = getCell(board, row, col);
            if(cell == '\0') {
                cell = ' ';
            }
            printf("%c", cell);
        }
        printf("|\n");
    }
    
    printf("+");
    for(unsigned int col = 0; col < kBoardCols; col++) {
        printf("-");
    }
    printf("+\n");
}

int main() {
    board_t board = makeBoard();
    if(board == NULL) {
        return EXIT_FAILURE;
    }

    setCell(board, 0, 0, 'K');
    setCell(board, 0, 1, 'o');
    setCell(board, 0, 2, 'n');
    setCell(board, 0, 3, 'o');

    setCell(board, 1, 1, 'D');
    setCell(board, 1, 2, 'i');
    setCell(board, 1, 3, 'a');
    setCell(board, 1, 4, 'v');
    setCell(board, 1, 5, 'o');
    setCell(board, 1, 6, 'l');
    setCell(board, 1, 7, 'o');

    
    setCell(board, 2, 2, 'D');
    setCell(board, 2, 3, 'a');

    printBoard(board);

    delBoard(board);
    return EXIT_SUCCESS;
}
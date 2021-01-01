#include <stdlib.h>
#include <stdio.h>

#include "chessConst.h"
#include "board.h"

void printBoard(board_t board) {
    
}

int main() {
    board_t board = makeBoard();
    if(board == NULL) {
        printf("failed to allocate board, exit failure\n");
        return EXIT_FAILURE;
    }

    delBoard(board);
    printf("test complete, exit success\n");
    return EXIT_SUCCESS;
}

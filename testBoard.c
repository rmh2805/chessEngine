#include <stdlib.h>
#include <stdio.h>

#include "chessConst.h"
#include "printDisp.h"
#include "board.h"

int main() {
    board_t board = makeBoard();
    if(board == NULL) {
        printf("failed to allocate board, exit failure\n");
        return EXIT_FAILURE;
    }
    
    if(printInit() != EXIT_SUCCESS) {
        printf("Failed to initialize the display, exit failure\n");
        return EXIT_FAILURE;
    }
    
    setCell(board, 0, 0, kBishopVal, true);
    setCell(board, 0, 1, kKnightVal, false);
    
    printBoard(board);

    delBoard(board);
    printf("test complete, exit success\n");
    return EXIT_SUCCESS;
}

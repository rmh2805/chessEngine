#include <stdlib.h>
#include <stdio.h>

#include "chessConst.h"
#include "printDisp.h"
#include "board.h"
#include "chess.h"

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
    
    setBoard(board);
    
    printBoard(board);

    delBoard(board);
    printf("test complete, exit success\n");
    return EXIT_SUCCESS;
}

#include <stdlib.h>
#include <stdio.h>

#include "chessConst.h"
#include "printDisp.h"
#include "board.h"
#include "chess.h"

#define kBufSize 32

int main() {
    board_t board = makeBoard();
    if(board == NULL) {
        printf("failed to allocate board, exit failure\n");
        return EXIT_FAILURE;
    }
    
    if(printInit(board) != EXIT_SUCCESS) {
        printf("Failed to initialize the display, exit failure\n");
        return EXIT_FAILURE;
    }

    char buf [kBufSize];
    
    printBoard(board);
    printGetStr(buf, kBufSize);

    setBoard(board);

    printf("%s\n", buf);
    printBoard(board);
    printGetStr(buf, kBufSize);

    setCell(board, 3, 3, kKingVal, true);
    
    printf("%s\n", buf);
    printBoard(board);
    

    delBoard(board);
    printf("test complete, exit success\n");
    return EXIT_SUCCESS;
}

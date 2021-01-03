#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "board.h"
#include "chess.h"
#include "pieceMove.h"

#include "dispFunc.h"
#include "cursesDisp.h"
#include "printDisp.h"

#define kCursesArg "-c"

int main(int argc, char** argv) {
    //Parse arguments
    DispFunc dispFunc = getPrintDisp();

    for(int i = 1; i < argc; i++) {
        if(strncmp(kCursesArg, argv[i], strlen(kCursesArg)) == 0) {
            dispFunc = getCursesDisp();
        }
    }

    //Allocate the board and game stat tracker
    board_t board = makeBoard();
    if(board == NULL) {
        printf("Failed to allocate board. Exit failure\n");
        return EXIT_FAILURE;
    }

    gameStats_t stats = makeGameStats();
    if(stats == NULL) {
        printf("Failed to allocate game stat tracker. Exit failure\n");
        delBoard(board);
        return EXIT_FAILURE;
    }

    //Initialize the display
    if(dispFunc.InitDisp(board) != EXIT_SUCCESS) {
        printf("Failed to initialize the display. Exit failure\n");
        delBoard(board);
        delGameStats(stats);
        return EXIT_FAILURE;
    }

    //Run the tests
    moveLegal(stats, board, 0, 0, 1, 1);

    //Clean up
    delBoard(board);
    delGameStats(stats);
    
    dispFunc.CloseDisp();
}

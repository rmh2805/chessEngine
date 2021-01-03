#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "board.h"
#include "chess.h"
#include "pieceMove.h"

#include "dispFunc.h"
#include "cursesDisp.h"
#include "printDisp.h"

#define kPrintArg "-p"

int main(int argc, char** argv) {
    //Parse arguments
    DispFunc dispFunc = getCursesDisp();

    for(size_t i = 1; i < argc; i++) {
        if(strncmp(kPrintArg, argv[i], strlen(kPrintArg)) == 0) {
            dispFunc = getPrintDisp();
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

    //Run the tests

    //Clean up
    delBoard(board);
    delGameStats(stats);

}

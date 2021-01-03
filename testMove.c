#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "board.h"
#include "chess.h"
#include "chessConst.h"
#include "pieceMove.h"

#include "dispFunc.h"
#include "cursesDisp.h"
#include "printDisp.h"

#define kBufSize 255

#define kCursesArg "-c"

void doTest(DispFunc dispFunc, board_t board, gameStats_t stats, size_t startRow, size_t startCol, size_t endRow, size_t endCol);

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
    
    char buf[kBufSize];
    buf[0] = '\0';

    //Initialize the display
    if(dispFunc.InitDisp(board) != EXIT_SUCCESS) {
        printf("Failed to initialize the display. Exit failure\n");
        delBoard(board);
        delGameStats(stats);
        return EXIT_FAILURE;
    }

    //Run the tests
    setBoard(board);
    
    //Knight Tests
    dispFunc.DispHelp("Testing Knight Movement");
    doTest(dispFunc, board, stats, 0, 1, 2, 0);    
    doTest(dispFunc, board, stats, 0, 1, 2, 1);
    doTest(dispFunc, board, stats, 0, 1, 2, 2);
    
    //Bishop Tests
    dispFunc.DispHelp("Testing Bishop Movement");

    doTest(dispFunc, board, stats, 0, 2, 2, 4);
    
    clearCell(board, 1, 3);
    doTest(dispFunc, board, stats, 0, 2, 2, 4);
    doTest(dispFunc, board, stats, 0, 2, 5, 7);
    setCell(board, 1, 3, kPawnVal, true);
    
    clearCell(board, 1, 1);
    doTest(dispFunc, board, stats, 0, 2, 2, 0);
    setCell(board, 1, 1, kPawnVal, true);

    setCell(board, 5, 0, kBishopVal, true);
    doTest(dispFunc, board, stats, 5, 0, 6, 1);
    doTest(dispFunc, board, stats, 5, 0, 2, 3);
    doTest(dispFunc, board, stats, 5, 0, 1, 4);
    clearCell(board, 5, 0); 

    //Clean up
    delBoard(board);
    delGameStats(stats);
    
    dispFunc.CloseDisp();
}

void doTest(DispFunc dispFunc, board_t board, gameStats_t stats, size_t startRow, size_t startCol, size_t endRow, size_t endCol) {
    bool legal = moveLegal(stats, board, startRow, startCol, endRow, endCol);
    
    char buf [kBufSize];
    buf[0] = '\0';

    sprintf(buf, "Move from %c%c to %c%c was %s.", '1' + (char)startRow, 'A' + (char)startCol, '1' + (char)endRow, 'A' + (char)endCol, (legal) ? "legal" : "illegal");
    
    dispFunc.DispScore((isWhiteTurn(stats)) ? "White's turn" : "Black's turn");
    dispFunc.DispMsg(buf);
    dispFunc.DispBoard(board);
    dispFunc.GetStr(buf, kBufSize);
    
}

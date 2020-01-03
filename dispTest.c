#define _DEFAULT_SOURCE

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "chessConst.h"
#include "chessDisp.h"
#include "chessBoard.h"

int main (int argc, char** argv) {
    board_t board = makeBoard();
    if(board == NULL)
        return EXIT_FAILURE;
    
    int numRows = 0, numCols = 0;
    if(startDisp(&numRows, &numCols)) 
        return EXIT_FAILURE;
    
    startBoard(board);
    
    drawTurn("Turn 1. ");
    drawBoard(board);
    drawPrompt();
    
    getch();
    stopDisp();
    
    deleteBoard(board);
    
    return EXIT_SUCCESS;
}

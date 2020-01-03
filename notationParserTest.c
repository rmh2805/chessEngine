#define _DEFAULT_SOURCE

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "notationParser.h"
#include "chessDisp.h"
#include "chessBoard.h"
#include "chessGame.h"

int main (int argc, char**argv) {
    board_t board = makeBoard();
    if(board == NULL)
        return EXIT_FAILURE;
    startBoard(board);
    
    
    deleteBoard(board);    
        
    return EXIT_SUCCESS;
}

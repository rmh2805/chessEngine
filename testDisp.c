#include <stdlib.h>
#include <stdio.h>

#include "board.h"
#include "printDisp.h"
//#include "cursesDisp.h"
#include "chessConst.h"
#include "chess.h"
#include "dispFunc.h"

int main() {
    //Initialize the display function struct
    DispFunc dispFunc;

    dispFunc.InitDisp = printInit;
    dispFunc.CloseDisp = printStop;
    
    dispFunc.DispHelp = printHelpPrompt;
    dispFunc.DispBoard = printBoard;
    dispFunc.DispMsg = printMsg;
    dispFunc.DispScore = printScore;

    dispFunc.GetStr = printGetStr;
    
    //Allocate the board and initialize the display
    board_t board = makeBoard();
    if(board == NULL) {
        printf("Failed to initialize the board, exit failure\n");
        return EXIT_FAILURE;
    }

    if(dispFunc.InitDisp(board) != EXIT_SUCCESS) {
        printf("Failed to initialize the display, exit failure\n");
        return EXIT_FAILURE;
    }

    //Perform tests on the display functions
    
    dispFunc.DispHelp("Help display test...");

    

    //cleanup
    dispFunc.CloseDisp(); //shut down the display

    delBoard(board); //free the board

    return EXIT_SUCCESS;
}

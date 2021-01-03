#include <stdlib.h>
#include <stdio.h>

#include "board.h"
#include "printDisp.h"
#include "cursesDisp.h"
#include "chessConst.h"
#include "chess.h"
#include "dispFunc.h"

#define kBufSize 32

//#define _DO_PRINT_TEST_
#define _DO_CURSES_TEST_

int doDispTest(DispFunc dispFunc, char* buf);

int main() {
    //Initialize the display function struct
    DispFunc dispFunc;

    
    //Allocate the input buffer as an empty str
    char buf [kBufSize];
    buf[0] = '\0'; //Initialize as an empty str
    
#ifdef  _DO_PRINT_TEST_
    dispFunc.InitDisp = printInit;
    dispFunc.CloseDisp = printStop;
    
    dispFunc.DispHelp = printHelpPrompt;
    dispFunc.DispBoard = printBoard;
    dispFunc.DispMsg = printMsg;
    dispFunc.DispScore = printScore;

    dispFunc.GetStr = printGetStr;
    
    printf("\n\n==========<Testing Print Display>==========\n\n");
    if(doDispTest(dispFunc, buf) == EXIT_SUCCESS) {
        printf("\n\n==========<Print Display Test Success>==========\n\n");
    } else { 
        printf("\n\n==========<Print Display Test Failure>==========\n\n");
        return EXIT_FAILURE;
    }
#endif //_DO_PRINT_TEST_

#ifdef  _DO_CURSES_TEST_
    dispFunc.InitDisp = cursesInit;
    dispFunc.CloseDisp = cursesClose;
    
    dispFunc.DispHelp = cursesDispHelp;
    dispFunc.DispBoard = cursesDispBoard;
    dispFunc.DispMsg = cursesDispMsg;
    dispFunc.DispScore = cursesDispScore;

    dispFunc.GetStr = cursesGetStr;


    printf("\n\n==========<Testing Curses Display>==========\n\n");
    if(doDispTest(dispFunc, buf) == EXIT_SUCCESS) {
        printf("\n\n==========<Curses Display Test Success>==========\n\n");
    } else { 
        printf("\n\n==========<Curses Display Test Faliure>==========\n\n");
        return EXIT_FAILURE;
    }

#endif //_DO_CURSES_TEST_
    
    return EXIT_SUCCESS;
}


int doDispTest(DispFunc dispFunc, char* buf) {
    buf[0] = '\0'; //Reset the buffer as an empty string

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
    
    //Test the help display
    dispFunc.DispHelp("Help display test...");
    
    //Display the empty board
    dispFunc.DispScore("Blank Board Display Test");
    dispFunc.DispMsg("(Previous round's commands displayed here)");
    dispFunc.DispBoard(board);
    dispFunc.GetStr(buf, kBufSize);
    
    //Display the starting configuration
    setBoard(board);

    dispFunc.DispScore("Starting Board Display Test");
    dispFunc.DispMsg(buf);
    dispFunc.DispBoard(board);
    dispFunc.GetStr(buf, kBufSize);
    
    

    //cleanup
    dispFunc.CloseDisp(); //shut down the display

    delBoard(board); //free the board

    return EXIT_SUCCESS;
}

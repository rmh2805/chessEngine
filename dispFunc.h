#ifndef  _DISP_FUNC_H_
#define  _DISP_FUNC_H_

#include <stdlib.h>

#include "board.h" // board_t

typedef struct DispFunc_s {
    int  (* InitDisp)(board_t board); //Initializes the display (board passed for size checks)
    void (* CloseDisp)(); //Used to safely shut down the display

    void (* DispHelp)(const char * msg); //Display the help message and wait for acknowledgement
    void (* DispBoard)(board_t board); //Display the board's current state
    void (* DispMsg)(const char * msg); //Display a message (below the score)
    void (* DispScore)(const char * score); //Display a score (top of screen)

    void (* GetStr)(char * buf, size_t bufSize); //Get a command from console (bottom of screen)

} DispFunc;

#endif //_DISP_FUNC_H_

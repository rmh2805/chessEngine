#include "boardDisp.h"

//=======================================<Module Constants>=======================================//
//==============================<Screenspace Definitions>===============================//
#define kColsPerCell 7
#define kRowsPerCell 5

#define kBoardWidth (kBoardCols * kColsPerCell + 4)
#define kBoardHeight (kBoardRows * kRowsPerCell + 6)

static int numRows = 0;
static int numCols = 0;

#define kMinCol ((int)(numCols/2) - (int)(kBoardWidth/2))
#define kMinRow ((int)(numRows/2) - (int)(kBoardHeight/2))

//=======================================<Helper Functions>=======================================//
unsigned int getCellLeftPos(unsigned int col) {
    if(col >= kBoardCols) {
        col = 0;
    }

    return kMinCol + col * kColsPerCell;
}

unsigned int getCellTopPos(unsigned int row) {
    if(row >= kBoardRows) {
        row = 0;
    }

    return kMinRow + row * kRowsPerCell;
}

//====================================<External Fuctionality>=====================================//
int startDisp() {
    return 1;
}

void stopDisp() {

}

void drawBoard(board_t board) {
    
}

void drawOver(const char* str) {
    
}

void drawUnder(const char* str) {

}


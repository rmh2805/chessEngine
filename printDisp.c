#include "printDisp.h"

#define kCellWidth 7
#define kCellHeight 4

#define kWhiteChar 'W'
#define kBlackChar 'B'

//========================================<Init and Close>=========================================//
int printInit(board_t board) {
    return EXIT_SUCCESS;
}

void printStop() {
    printf("Stopping Print Display\n");
}


//============================================<Display>============================================//
void printHelpPrompt(const char* helpMsg) {
    printf("%s\n\nPress enter to continue", helpMsg);
    fgetc(stdin);
}

//Declare print board helpers before use
void printColumnLabels(board_t board);
void printBoardRow(board_t board, size_t row);
void printHorizontalBorder(board_t board);

void printBoard(board_t board) {
    if(board == NULL)
        return;

    size_t nRows = getNRows(board);

    printColumnLabels(board);
    printHorizontalBorder(board);
    
    for(size_t dRow = 0; dRow < nRows; dRow++) {
        size_t row = nRows - 1 - dRow;
        printBoardRow(board, row);
    }
    

    printHorizontalBorder(board);
    printColumnLabels(board);
}

void printMsg(const char * msg) {
    printf("%s\n", msg);
}

void printScore(const char * score) {
    printf("===========================================================\n");
    printf("%s\n", score);
}

//=============================================<Input>=============================================//
void printGetStr(char * buf, size_t bufSize) {
    printf("Enter your command: ");
    fgets(buf, bufSize, stdin);
}

//============================================<Helpers>============================================//
void printHorizontalBorder(board_t board) {
    if(board == NULL)
        return;

    size_t nCols = getNCols(board);

    printf(" +");
    for(size_t col = 0; col < nCols * kCellWidth; col++)
        printf("=");
    printf("+\n");
}

void printBoardRow(board_t board, size_t row) {
    if(board == NULL || row >= getNRows(board)) {
        return;
    }
    
    size_t nCols = getNCols(board); 
    
    for(size_t cellRow = 0; cellRow < kCellHeight; cellRow++) {
        if(cellRow == kCellHeight/2) {
            printf("%c", (char)(row + '1'));
        } else {
            printf(" ");
        }
        printf("|");

        for(size_t col = 0; col < nCols; col++) {
            char spaceChar = ((row + col) % 2 == 0) ? ' ':'#';
            
            for(size_t cellCol = 0; cellCol < kCellWidth; cellCol++) {
                //todo instead print the value and color of the piece in each cell, but this is fine for now
                if(cellRow == kCellHeight/2 && cellCol == kCellWidth/2 - 1) {
                    char cell = getCell(board, row, col);
                    bool isWhite = cell & kWhiteFlag;
                    cell = cell & kColorMask;
                    
                    printf("%c", (cell == kEmptyCell) ? spaceChar : ((isWhite) ? kWhiteChar : kBlackChar));
                    cellCol += 1;
                    
                    cell = pieceDispFromVal(cell);
            
                    printf("%c", (cell == kEmptyCell) ? spaceChar : cell);
                    
                } else {
                    printf("%c", spaceChar);
                }
            }

        }

        printf("|");
        if(cellRow == kCellHeight/2) {
            printf("%c", (char)(row + '1'));
        }
        printf("\n");
    }    

}

void printColumnLabels(board_t board) {
    if(board == NULL)
        return;

    size_t nCols = getNCols(board);
    
    printf("  ");
    for(size_t col = 0; col < nCols; col++) {
        for(size_t i = 0; i < kCellWidth; i++) {
            if(i == kCellWidth/2) { 
                printf("%c", (char)(col + 'A'));
            } else {
                printf(" ");
            }
        }
    }
    printf("\n");

}

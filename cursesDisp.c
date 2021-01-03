#include "cursesDisp.h"

//=======================================<Display Constnts>========================================//
#define kCellWidth 11
#define kCellHeight 5

#define kPieceWidth 5
#define kPieceHeight 3

static size_t screenWidth = 0;
static size_t screenHeight = 0;

static size_t textCol = 0;
static size_t scoreRow = 0;
static size_t msgRow = 0;
static size_t promptRow = 0;

size_t getCellRow(size_t cellRow, size_t nRows);
size_t getCellCol(size_t cellCol, size_t nCols);

//=======================================<Palette Constants>=======================================//
#define kBasePalette 0
#define kWhitePalette 1
#define kBlackPalette 2

//========================================<Init and Close>=========================================//

DispFunc getCursesDisp() {
    DispFunc dispFunc;

    dispFunc.InitDisp = cursesInit;
    dispFunc.CloseDisp = cursesClose;

    dispFunc.DispHelp = cursesDispHelp;
    dispFunc.DispBoard = cursesDispBoard;
    dispFunc.DispMsg = cursesDispMsg;
    dispFunc.DispScore = cursesDispScore;

    dispFunc.GetStr = cursesGetStr;

    return dispFunc;
}

int cursesInit(board_t board) {
    if(board == NULL) return EXIT_FAILURE; //Must have a board to initialize (to check for size)

    initscr(); //Start curses mode

    //Check screen size
    getmaxyx(stdscr, screenHeight, screenWidth);
    
    size_t boardRows = getNRows(board);
    size_t boardCols = getNCols(board);
    
    /* Screen space requirements:
     * - 2 rows, cols of space around the board (one on each side)
     * - 4 rows of text around the board (2 above, 1 below (one unused below to simplify the math)
     * - 2 rows, cols of border characters (along each side)
     * - 2 rows, cols of rank/file indicators (along each side)
     * - (kCellHeight * boardRows) rows for the board
     * - (kCellWidth * boardCols) cols for the board 
     */

    if(boardRows * kCellHeight + 10 > screenHeight || boardCols * kCellWidth + 6 > screenWidth) {
        endwin();
        printf("Error: console window too small\n");
        return EXIT_FAILURE;
    }
    

    //Check for color support and assign palettes

    if(!has_colors()) {
        endwin();
        printf("Error: console does not support color\n");
        return EXIT_FAILURE;
    }

    start_color();
    init_pair(kWhitePalette, COLOR_BLACK, COLOR_WHITE);
    init_pair(kBlackPalette, COLOR_WHITE, COLOR_BLACK);
    
    //Calculate and save text region coordinates
    textCol = getCellCol(0, boardCols) - 2;
    scoreRow = getCellRow(0, boardRows) - 5;
    msgRow = scoreRow + 1;
    promptRow = getCellRow(8, boardRows) + 3;
    
    //Clear the screen and exit success
    refresh();
    return EXIT_SUCCESS;
}

void cursesClose() {
    endwin();
}

//============================================<Display>============================================//
void cursesDispHelp(const char * msg) {
    erase();
    mvprintw(0, 0, msg);
    printw("\nPress Enter to continue...");
    mvgetch(0, 0);
    erase();
}

void drawBaseBoard(size_t boardRows, size_t boardCols);
void drawBoardIndicators(size_t boardRows, size_t boardCols);

void cursesDispBoard(board_t board) {
    size_t boardRows = getNRows(board);
    size_t boardCols = getNCols(board);

    drawBaseBoard(boardRows, boardCols);
    drawBoardIndicators(boardRows, boardCols);
    
    for(size_t boardRow = 0; boardRow < boardRows; boardRow++) {
        size_t screenRow = getCellRow(boardRows - 1 - boardRow, boardRows) + kCellHeight/2 - kPieceHeight/2;

        for(size_t boardCol = 0; boardCol < boardCols; boardCol++) {
            size_t screenCol = getCellCol(boardCol, boardCols) + kCellWidth/2 - kCellHeight/2;

            char cell = getCell(board, boardRow, boardCol);
            size_t palette = (cell & kWhiteFlag) ? kWhitePalette : kBlackPalette;
            cell = pieceDispFromVal(cell);

            if(cell == kEmptyCell) continue;            

            wattron(stdscr, COLOR_PAIR(palette));
            
            for(size_t dRow = 0; dRow < kPieceHeight; dRow++) {
                for(size_t dCol = 0; dCol < kPieceWidth; dCol++) {
                    char dispCh = ' ';
                    
                    if(dRow == kPieceHeight/2 && dCol == kPieceWidth/2) {
                        dispCh = cell;
                    } else if((dRow == 0 || dRow == kPieceHeight-1) && (dCol == 0 || dCol == kPieceWidth-1)) {
                        dispCh = '+';
                    } else if(dRow == 0 || dRow == kPieceHeight-1){
                        dispCh = '=';
                    } else if(dCol == 0 || dCol == kPieceWidth-1) {
                        dispCh = '|';
                    }
                    
                    mvaddch(screenRow + dRow, screenCol + dCol, dispCh);
                }
            }

            refresh();
            wattroff(stdscr, COLOR_PAIR(palette)); 
        }
    }

    refresh();
}

void cursesDispMsg(const char * msg) {
    move(msgRow, textCol);
    clrtoeol();
    mvprintw(msgRow, textCol, "%s", msg);
}

void cursesDispScore(const char * score) {
    move(scoreRow, textCol);
    clrtoeol();
    mvprintw(scoreRow, textCol, "%s", score);
}

//=============================================<Input>=============================================//
void cursesGetStr(char * buf, size_t bufSize) {
    move(promptRow, textCol);
    clrtoeol();
    mvprintw(promptRow, textCol, "\tEnter your command: ");
    getnstr(buf, bufSize);
}

//============================================<Helpers>============================================//
size_t getCellRow(size_t row, size_t nRows) {
    return (screenHeight == 0) ? 0 : screenHeight/2 - (kCellHeight * nRows) / 2 + row * kCellHeight;
}

size_t getCellCol(size_t col, size_t nCols) {
    return (screenWidth == 0) ? 0 : screenWidth/2 - (kCellWidth * nCols) / 2 + col * kCellWidth;
}

void drawBaseBoard(size_t boardRows, size_t boardCols) {
    //Draw the borders
    size_t topRow = getCellRow(0, boardRows) - 1;
    size_t bottomRow = getCellRow(boardRows, boardRows);
    size_t lCol = getCellCol(0, boardCols) - 1;
    size_t rCol = getCellCol(boardCols, boardCols);

    mvaddch(topRow, lCol, '+');
    mvaddch(topRow, rCol, '+');
    mvaddch(bottomRow, lCol, '+');
    mvaddch(bottomRow, rCol, '+');

    for(size_t col = lCol + 1; col < rCol; col++) {
        mvaddch(topRow, col, '=');
        mvaddch(bottomRow, col, '=');
    }

    for(size_t row = topRow + 1; row < bottomRow; row++) {
        mvaddch(row, lCol, '|');
        mvaddch(row, rCol, '|');
    }

    //Draw the checkerboard pattern
    for(size_t dispRow = 0; dispRow < boardRows; dispRow++) {
        topRow = getCellRow(dispRow, boardRows);
        
        for(size_t dispCol = 0; dispCol < boardCols; dispCol++) {
            lCol = getCellCol(dispCol, boardCols);
            
            size_t palette = ((dispRow + dispCol) % 2 == 1) ? kBlackPalette : kWhitePalette;
            wattron(stdscr, COLOR_PAIR(palette));
            
            for(size_t dRow = 0; dRow < kCellHeight; dRow++) {
                for(size_t dCol = 0; dCol < kCellWidth; dCol++) {
                    mvaddch(topRow + dRow, lCol + dCol, ' ');
                }
            }
            refresh();
            wattroff(stdscr, COLOR_PAIR(palette));
        }
    }
}

void drawBoardIndicators(size_t boardRows, size_t boardCols) {
    //Calculate the indic rows and cols
    size_t topRow = getCellRow(0, boardRows) - 2;
    size_t bottomRow = getCellRow(boardRows, boardRows) + 1;
    size_t lCol = getCellCol(0, boardCols) - 2;
    size_t rCol = getCellCol(boardCols, boardCols) + 1;
    
    //Print the file indicators
    for(size_t dispCol = 0; dispCol < boardCols; dispCol++) {
        mvaddch(topRow, getCellCol(dispCol, boardCols) + kCellWidth/2, 'A' + dispCol);
        mvaddch(bottomRow, getCellCol(dispCol, boardCols) + kCellWidth/2, 'A' + dispCol);
    }

    //Print the rank indicators
    for(size_t dispRow = 0; dispRow < boardRows; dispRow++) {
        mvaddch(getCellRow(dispRow, boardRows) + kCellHeight/2, lCol, '0' + boardRows - dispRow);
        mvaddch(getCellRow(dispRow, boardRows) + kCellHeight/2, rCol, '0' + boardRows - dispRow);
    }
}


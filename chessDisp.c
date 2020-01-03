#include "chessDisp.h"

#define whitePalette 2
#define blackPalette 3

#define kCellWidth 7
#define kCellHeight 5

#define kPieceWidth 5
#define kPieceHeight 3

#define kBoardWidth kCellWidth * kNumFiles
#define kBoardHeight kCellHeight * kNumRanks

static int numRows = 0;
static int numCols = 0;

#define kMinCol (int)(numCols / 2) - (int)(kBoardWidth / 2)
#define kMaxCol kMinCol + kBoardWidth - 1
#define kMinRow (int)(numRows / 2) - (int)(kBoardHeight / 2)
#define kMaxRow kMinRow + kBoardHeight - 1

#define GET_LEFT_COL(fileIn) kMinCol + (int)(fileIn - 'a') * kCellWidth
#define GET_TOP_ROW(rankIn) (kMaxRow - (rankIn) * kCellHeight) + 1

int startDisp(int* lNumRows, int* lNumCols) {
    //Start the curses environment and find the boundries of the window
    initscr();  // Start curses mode
    
    getmaxyx(stdscr, *lNumRows, *lNumCols);
    numRows = *lNumRows;
    numCols = *lNumCols;

    if(numRows < kBoardHeight + 6 || numCols < kBoardWidth + 6){ 
        endwin(); 
        printf("Your terminal scren is too small, must have at least %d rows and %d cols\n", kBoardHeight + 2, kBoardWidth + 2);
        return 1;
    } 
    
    if (has_colors() == FALSE) { 
        endwin(); 
        printf("Your terminal does not support color\n");
        return 1;
    } 
    
    start_color();
    init_pair(whitePalette, COLOR_BLACK, COLOR_WHITE);
    init_pair(blackPalette, COLOR_WHITE, COLOR_BLACK);
    
    return 0;
}

int stopDisp () {
    endwin(); 
    return 0;
}

void drawCell(int rank, char file) {
    int minRow = GET_TOP_ROW(rank);
    int minCol = GET_LEFT_COL(file);
    
    int palette = whitePalette;
    if(((int)(file - 'a') + rank - 1) % 2 == 1)
        palette = blackPalette;
    
    wattron(stdscr, COLOR_PAIR(palette));
    for(int row = minRow; row < minRow + kCellHeight; row++) {
        for(int col = minCol; col < minCol + kCellWidth; col++) {
            mvprintw(row, col, " ");
        }
    }
    refresh();
    wattroff(stdscr, COLOR_PAIR(palette));
    move(0,0);
}

void drawPiece(board_t board, int rank, char file) {
    if(cellEmpty(board, rank, file))
        return;
    
    int palette = blackPalette;
    if(pieceWhite(board, rank, file)){
        palette = whitePalette;
    }
    wattron(stdscr, COLOR_PAIR(palette));
    
    int minRow = (GET_TOP_ROW(rank) + kCellHeight / 2) - kPieceHeight/2;
    int minCol = (GET_LEFT_COL(file) + kCellWidth / 2) - kPieceWidth/2;
    for(int row = minRow; row < minRow + kPieceHeight; row++) {
        for(int col = minCol; col < minCol + kPieceWidth; col++) {
            mvaddch(row, col, ' ');
        }
    }
    
    mvaddch(minRow, minCol, '+');
    mvaddch(minRow + kPieceHeight - 1, minCol, '+');
    mvaddch(minRow, minCol + kPieceWidth - 1, '+');
    mvaddch(minRow + kPieceHeight - 1, minCol + kPieceWidth - 1, '+');
    
    for(int row = minRow + 1; row < minRow + kPieceHeight - 1; row++) {
        mvaddch(row, minCol, '|');
        mvaddch(row, minCol + kPieceWidth - 1, '|');
    }
    
    for(int col = minCol + 1; col < minCol + kPieceWidth - 1; col++) {
        mvaddch(minRow, col, '-');
        mvaddch(minRow + kPieceHeight - 1, col, '-');
    }
    
    char piece = pieceType(board, rank, file);
    mvaddch(GET_TOP_ROW(rank) + kCellHeight / 2, GET_LEFT_COL(file) + kCellWidth/2, piece);
    refresh();
    wattroff(stdscr, COLOR_PAIR(palette));
    move(0, 0);
}

void drawTurn(const char * turn) {
    mvprintw(kMinRow - 3, kMinCol, "                                                 ");
    mvprintw(kMinRow - 3, kMinCol, turn);
    refresh();
}

void drawPrompt() {
    mvprintw(kMaxRow + 3, kMinCol, "                                                 ");
    mvprintw(kMaxRow + 3, kMinCol, "Please select your move: ");
}

void drawBorder() {
    mvprintw(kMinRow - 1, kMinCol - 1, "+");
    mvprintw(kMaxRow + 1, kMinCol - 1, "+");
    mvprintw(kMinRow - 1, kMaxCol + 1, "+");
    mvprintw(kMaxRow + 1, kMaxCol + 1, "+");
    for(int col = kMinCol; col < kMinCol + kBoardWidth; col++) {
        mvprintw(kMinRow - 1, col, "-");
        mvprintw(kMaxRow + 1, col, "-");
    }
    
    for(int row = kMinRow; row < kMinRow + kBoardHeight; row++) {
        mvprintw(row, kMinCol - 1, "|");
        mvprintw(row, kMaxCol + 1, "|");
    }
    
    for(int rank = 1; rank < 1 + kNumRanks; rank++) {
        int row = GET_TOP_ROW(rank) + kCellHeight / 2;
        mvaddch(row, kMinCol-2, '0' + rank); 
        mvaddch(row, kMaxCol+2, '0' + rank); 
    }
    
    for(char file = 'a'; file < 'a' + kNumFiles; file++) {
        int col = GET_LEFT_COL(file) + kCellWidth/2;
        mvaddch(kMinRow-2, col, file);
        mvaddch(kMaxRow+2, col, file);
    }
    
    refresh();
    move(0, 0);
}

void drawBoard(board_t board) {
    for(int rank = 1; rank < 1 + kNumRanks; rank++) {
        for(char file = 'a'; file < 'a' + kNumFiles; file++) {
            drawCell(rank, file);
            drawPiece(board, rank, file);
        }  
    }
    
    drawBorder();
    
    move(0,0);
    refresh();
}

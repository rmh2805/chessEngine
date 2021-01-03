#include "pieceMove.h"

struct gameStats_s {
    size_t whiteEnPasseCol; //The column in which white can be captured en passent
    size_t blackEnPasseCol; //The column in which black can be captured en passent

    bool isWhiteTurn : 1; //Is it white's turn
    
    bool wCastleK : 1; //Can white king-side castle
    bool wCastleQ : 1; //Can white queen-side castle

    bool bCastleK : 1; //Can black king-side castle
    bool bCastleQ : 1; //can black queen-side castle
};

//===================================================<Memory Management>===================================================//
gameStats_t makeGameStats() {
    gameStats_t stats = malloc(sizeof(struct gameStats_s));

    stats->whiteEnPasseCol = 255;
    stats->blackEnPasseCol = 255;

    stats->isWhiteTurn = true;
    
    stats->wCastleK = true;
    stats->wCastleQ = true;

    stats->bCastleK = true;
    stats->bCastleQ = true;

    return stats;
}

void delGameStats(gameStats_t stats) {
    free(stats);
}

//=====================================================<Move Legality>=====================================================//
bool bishopLegal(board_t board, size_t startRow, size_t startCol, size_t endRow, size_t endCol);
bool rookLegal(board_t board, size_t startRow, size_t startCol, size_t endRow, size_t endCol);

#include <stdio.h>
bool moveLegal(gameStats_t stats, board_t board, size_t startRow, size_t startCol, size_t endRow, size_t endCol) {
    if(board == NULL || stats == NULL) {
        printf("invalid ADTs");
        return false;
    }

    //Ensure all coords are in bounds
    size_t boardRows = getNRows(board);
    size_t boardCols = getNCols(board);

    if(startRow > boardRows || endRow > boardRows || startCol > boardCols || endCol > boardCols) {
        printf("out of bounds");
        return false;
    }

    //check that the selected cell is owned by the player
    char startCell = getCell(board, startRow, startCol);

    bool isWhite = (startCell & kWhiteFlag) ? true : false;
    if(startCell == kEmptyCell || (isWhite != stats->isWhiteTurn)) {
        printf("Not your piece");
        return false;
    }

    startCell = startCell & kColorMask;

    //return false if dest cell is one of the player's pieces
    char dstCell = getCell(board, endRow, endCol);
    bool dstEmpty = dstCell == kEmptyCell;

    isWhite = (dstCell & kWhiteFlag) ? true : false;
    if(!dstEmpty && isWhite == stats->isWhiteTurn) {
        printf("dest is your piece");
        return false;
    }
    
    dstCell = dstCell & kColorMask;
    
    //Calculate deltas
    size_t dRow = (endRow > startRow) ? endRow - startRow : startRow - endRow;
    size_t dCol = (endCol > startCol) ? endCol - startCol : startCol - endCol;

    //Check that dst != start
    if(dRow == 0 && dCol == 0) {
        return false;
    }

    //Check for illegal knight moves
    if(startCell == kKnightVal && !((dRow == 1 && dCol == 2) || (dRow == 2 && dCol == 1))) {
        return false;
    }
    
    //Check if legal queen, bishop, or rook moves
    switch(startCell) {
        case kBishopVal:
            if(!bishopLegal(board, startRow, startCol, endRow, endCol)) 
                return false;
            break; 
    } 

    //check if legal king move (incl castling)

    //check if legal pawn move (incl en passent)

    //Check if left in check afterwards 


    return true;
}


bool makeMove(gameStats_t stats, board_t board, size_t startRow, size_t startCol, size_t endRow, size_t endCol) {
    return false;
}

//=======================================================<Getters>========================================================//
bool isWhiteTurn(gameStats_t stats) {
    if(stats == NULL) return false;
    return stats->isWhiteTurn;
}

//========================================================<Helpers>========================================================//
bool bishopLegal(board_t board, size_t startRow, size_t startCol, size_t endRow, size_t endCol) {
    
    size_t dRow = (endRow > startRow) ? endRow - startRow : startRow - endRow;
    size_t dCol = (endCol > startCol) ? endCol - startCol : startCol - endCol;

    if(dRow != dCol)
       return false;

    for(size_t d = 1; d < dRow; d++) {
        size_t row = (endRow > startRow) ? startRow + d : startRow - d;
        size_t col = (endCol > startCol) ? startCol + d : startCol - d;

        if(getCell(board, row, col) != kEmptyCell)
            return false;
    }

    return true;
}

bool rookLegal(board_t board, size_t startRow, size_t startCol, size_t endRow, size_t endCol);

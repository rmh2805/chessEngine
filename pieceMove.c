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

gameStats_t makeGameStats() {
    return NULL;
}

void delGameStats(gameStats_t stats) {

}

bool moveLegal(gameStats_t stats, board_t board, size_t startRow, size_t startCol, size_t endRow, size_t endCol) {
    return false;
}

bool makeMove(gameStats_t stats, board_t board, size_t startRow, size_t startCol, size_t endRow, size_t endCol) {
    return false;
}



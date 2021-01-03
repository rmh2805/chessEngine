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

#include <stdio.h>
bool moveLegal(gameStats_t stats, board_t board, size_t startRow, size_t startCol, size_t endRow, size_t endCol) {
    if(board == NULL || stats == NULL) {
        return false;
    }
    
    printf("White en passe col: %lu\n", stats->whiteEnPasseCol);
    printf("Black en passe col: %lu\n", stats->blackEnPasseCol);
    
    printf("%s\n", (stats->isWhiteTurn) ? "white's turn" : "black's turn");
    printf("%s\n", (stats->wCastleK) ? "white can king castle" : "white can't king castle");
    

    return false;
}

bool makeMove(gameStats_t stats, board_t board, size_t startRow, size_t startCol, size_t endRow, size_t endCol) {
    return false;
}



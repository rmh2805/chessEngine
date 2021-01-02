#include "chess.h"

void setBoard(board_t board) {
    if(board == NULL)
        return;

    for(size_t col = 0; col < 8; col++) {
        setCell(board, 1, col, kPawnVal, true);
        setCell(board, 6, col, kPawnVal, false);
    }

    setCell(board, 0, 0, kRookVal, true);
    setCell(board, 0, 7, kRookVal, true);
    setCell(board, 7, 0, kRookVal, false);
    setCell(board, 7, 7, kRookVal, false);

    setCell(board, 0, 1, kKnightVal, true);
    setCell(board, 0, 6, kKnightVal, true);
    setCell(board, 7, 1, kKnightVal, false);
    setCell(board, 7, 6, kKnightVal, false);

    setCell(board, 0, 2, kBishopVal, true);
    setCell(board, 0, 5, kBishopVal, true);
    setCell(board, 7, 2, kBishopVal, false);
    setCell(board, 7, 5, kBishopVal, false);

    setCell(board, 0, 3, kQueenVal, true);
    setCell(board, 7, 3, kQueenVal, false);
    
    setCell(board, 0, 4, kKingVal, true);
    setCell(board, 7, 4, kKingVal, false);
}
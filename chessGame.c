#include "chessGame.h"


void startBoard(board_t board){
    if(board == NULL)
        return;

    for(char file = 'a'; file < 'a' + kNumFiles; file++) {
        setPiece(board, true, kPawnFlag, 2, file);
        setPiece(board, false, kPawnFlag, 7, file);
    }

    setPiece(board, true, kRookFlag, 1, 'a');
    setPiece(board, true, kRookFlag, 1, 'h');
    setPiece(board, false, kRookFlag, 8, 'a');
    setPiece(board, false, kRookFlag, 8, 'h');

    setPiece(board, true, kKnightFlag, 1, 'b');
    setPiece(board, true, kKnightFlag, 1, 'g');
    setPiece(board, false, kKnightFlag, 8, 'b');
    setPiece(board, false, kKnightFlag, 8, 'g');

    setPiece(board, true, kBishopFlag, 1, 'c');
    setPiece(board, true, kBishopFlag, 1, 'f');
    setPiece(board, false, kBishopFlag, 8, 'c');
    setPiece(board, false, kBishopFlag, 8, 'f');

    setPiece(board, true, kQueenFlag, 1, 'd');
    setPiece(board, false, kQueenFlag, 8, 'd');

    setPiece(board, true, kKingFlag, 1, 'e');
    setPiece(board, false, kKingFlag, 8, 'e');
}


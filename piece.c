#include "piece.h"

const char kPieceTypes[] ={kPawnFlag, kRookFlag, kKnightFlag, kBishopFlag, kQueenFlag, kKingFlag};
const int kNumPieceTypes = sizeof(kPieceTypes)/sizeof(kPieceTypes[0]);


bool isPiece (char piece) {
    for(int i = 0; i < kNumPieceTypes; i++) {
        if(kPieceTypes[i] == piece)
            return true;
    }
    return false;
}

bool pawnMove (board_t board, char srcFile, int srcRank, char destFile, int destRank) {
    bool isWhite = pieceWhite(board, srcRank, srcFile);
    
    if(srcRank == destRank || //If no rank change or
            isWhite != (srcRank < destRank) ||  //retreating pawns or
            abs(srcRank - destRank) > 2) //Advance more than max (2)
        return false;
    
    
    if(abs(srcFile - destFile) == 1 && abs(srcRank - destRank) == 1) {
        //Capture Check
    }
    
    return false;
}

bool rookMove (board_t board, char srcFile, int srcRank, char destFile, int destRank) {
    return false;
}

bool knightMove (board_t board, char srcFile, int srcRank, char destFile, int destRank) {
    return false;
}

bool bishopMove (board_t board, char srcFile, int srcRank, char destFile, int destRank) {
    return false;
}

bool queenMove (board_t board, char srcFile, int srcRank, char destFile, int destRank) {
    return false;
}

bool kingMove (board_t board, char srcFile, int srcRank, char destFile, int destRank) {
    return false;
}

bool canMove (board_t board, char srcFile, int srcRank, char destFile, int destRank) {
    if(board == NULL)
        return false;
    
    bool isWhite = pieceWhite(board, srcRank, srcFile);
    char piece = pieceType(board, srcRank, srcFile);
    switch(piece) {
        case kPawnFlag:
            return pawnMove(board, srcFile, srcRank, destFile, destRank);
        case kRookFlag:
            return rookMove(board, srcFile, srcRank, destFile, destRank);
        case kKnightFlag:
            return knightMove(board, srcFile, srcRank, destFile, destRank);
        case kBishopFlag:
            return bishopMove(board, srcFile, srcRank, destFile, destRank);
        case kQueenFlag:
            return queenMove(board, srcFile, srcRank, destFile, destRank);
        case kKingFlag:
            return kingMove(board, srcFile, srcRank, destFile, destRank);
        default:
            return false;
        
    }
}

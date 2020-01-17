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

bool colorMatch (board_t board, int rank, char file, bool isWhite) {
    if(board == NULL)
        return false;
    
    return (isWhite && pieceWhite(board, rank, file)) || (!isWhite && pieceBlack(board, rank, file));
}

bool cardinalMove (board_t board, bool isWhite, int deltaRank, int deltaFile, int srcRank, char srcFile, int destRank, char destFile) {
    if(srcRank == destRank && srcFile == destFile)
        return cellEmpty(board, srcRank, srcFile) || (isWhite != pieceWhite(board, srcRank, srcFile));
    
    if(!cellEmpty(board, srcRank, srcFile))
        return false;
    
    return cardinalMove(board, isWhite, deltaRank, deltaFile, srcRank + deltaRank, srcFile + deltaFile, destRank, destFile);
    
    
}

//Checks if a pawn move is legal at all (excluding en passent, as that requires knowledge of the previous move)
bool pawnMove (board_t board, int srcRank, char srcFile, int destRank, char destFile) {
    bool isWhite = pieceWhite(board, srcRank, srcFile);
    
    if(srcRank == destRank ||                   //If no rank change or
            isWhite != (srcRank < destRank) ||  //retreating pawns or
            abs(srcRank - destRank) > 2) {      //Advance more than max (2)
                
        return false;
    } else if(abs(srcFile - destFile) == 1 && abs(srcRank - destRank) == 1) {
        //Capture Check
        if(cellEmpty(board, destRank, destFile)) {
            return false;
        }
        
        bool opponentWhite = pieceWhite(board, destRank, destFile);
        return isWhite != opponentWhite;
        
    } else if(abs(srcFile - destFile) != 0) {
        return false; //Pawns can only change file on capture
    } else if(abs(srcRank - destRank) == 1) {
        return cellEmpty(board, destRank, destFile);    //Check if dest Empty
    }
    
    //First check if this is the pawn's initial deployment, if so allow an advance of 2, else disallow
    return ((isWhite && srcRank == 2)||(!isWhite && srcRank == 7)) && abs(srcRank - destRank) == 2;
}

bool rookMove (board_t board, int srcRank, char srcFile, int destRank, char destFile) {
    if((srcRank == destRank && srcFile == destFile) ||
       (srcRank != destRank && srcFile != destFile))
        return false;
    
    bool isWhite = pieceWhite(board, srcRank, srcFile);
    int deltaRank = 0;
    int deltaFile = 0;
    
    
    if(srcRank > destRank) {
        //Decrasing its rank
        deltaRank = -1;
    } else if (srcRank < destRank) {
        //Increasing its rank
        deltaRank = 1;
    } else if (srcFile > destFile) {
        //Decreasing its file
        deltaFile = -1;
    } else {
        //Increasing its file
        deltaFile = 1;
    }
    
    return cardinalMove(board, isWhite, deltaRank, deltaFile, srcRank + deltaRank, srcFile + deltaFile, destRank, destFile);
}

bool knightMove (board_t board, int srcRank, char srcFile, int destRank, char destFile) {
    int dRank = abs(srcRank - destRank);
    int dFile = abs(srcFile - destFile);
    if((dRank != 2 && dFile != 1)&&(dRank != 1 && dFile != 2)) {
        return false;
    }
    
    return cellEmpty(board, destRank, destFile) || (pieceWhite(board, srcRank, srcFile) != pieceWhite(board, destRank, destFile));
}

bool bishopMove (board_t board, int srcRank, char srcFile, int destRank, char destFile) {
    if((srcRank == destRank && srcFile == destFile) || 
       (abs(srcRank - destRank) != abs(srcFile - destFile)))
       return false;
        
    bool isWhite = pieceWhite(board, srcRank, srcFile);
    int deltaRank = (srcRank > destRank) ? -1 : 1;
    int deltaFile = (srcFile > destFile) ? -1 : 1;

    
    
    return cardinalMove(board, isWhite, deltaRank, deltaFile, srcRank + deltaRank, srcFile + deltaFile, destRank, destFile);
}

bool queenMove (board_t board, int srcRank, char srcFile, int destRank, char destFile) {
    return bishopMove(board, srcRank, srcFile, destRank, destFile) || rookMove(board, srcRank, srcFile, destRank, destFile);
}

//Does not calculate check, mate, or castling, only base movement and capture
bool kingMove (board_t board, int srcRank, char srcFile, int destRank, char destFile) {
    if((abs(srcRank - destRank) > 1 || 
        abs(srcFile - destFile) > 1) || 
        (srcRank == destRank && srcFile == destFile))
        return false;
    
    
    
    return cellEmpty(board, destRank, destFile) || (pieceWhite(board, srcRank, srcFile) != pieceWhite(board, destRank, destFile));
}

bool canMove (board_t board, int srcRank, char srcFile, int destRank, char destFile) {
    if(board == NULL)
        return false;
    
    char piece = pieceType(board, srcRank, srcFile);
    switch(piece) {
        case kPawnFlag:
            return pawnMove(board, srcRank, srcFile, destRank, destFile);
        case kRookFlag:
            return rookMove(board, srcRank, srcFile, destRank, destFile);
        case kKnightFlag:
            return knightMove(board, srcRank, srcFile, destRank, destFile);
        case kBishopFlag:
            return bishopMove(board, srcRank, srcFile, destRank, destFile);
        case kQueenFlag:
            return queenMove(board, srcRank, srcFile, destRank, destFile);
        case kKingFlag:
            return kingMove(board, srcRank, srcFile, destRank, destFile);
        default:
            return false;
        
    }
}

#include "chessBoard.h"

void deleteBoard (board_t board) {
    if(board == NULL)
        return;
    
    if(board->data != NULL) {
        for(int i = 0; i < kNumRanks; i++) {
            if(board->data[i] == NULL) {
                free(board->data[i]);
            }
        }
        
        free(board->data);
    }
    
    free(board);
}

board_t makeBoard () {
    //Allocate the board itself
    board_t board = calloc(1, sizeof(struct board_s));
    if(board == NULL) 
        return NULL;
    
    board->data = calloc(kNumRanks, sizeof(char*));
    
    if(board->data == NULL) {
        deleteBoard(board);
        return NULL;
    }
    
    for(int i = 0; i < kNumFiles; i++) {
        board->data[i] = calloc(kNumFiles * 2 + 1, sizeof(char));
        if(board->data[i] == NULL) {
            deleteBoard(board);
            return NULL;
        }
    }
    
    for(int r = 0; r < kNumRanks; r++) {
        char* rank = board->data[r];
        for(int f = 0; f < kNumFiles; f++) {
            rank[f*2] = ' ';
            rank[f*2 + 1] = ' ';
        }
    }
    
    
    return board;
}

bool pieceWhite(board_t board, int rank, char file) {
    if(board == NULL || !isRank(rank) || !isFile(file))
        return false;
    
    return board->data[rank - 1][(file - 'a') * 2] == kWhiteFlag;
}

bool pieceBlack(board_t board, int rank, char file) {
    if(board == NULL || !isRank(rank) || !isFile(file))
        return false;
    
    return board->data[rank - 1][(file - 'a') * 2] == kBlackFlag;
}

bool cellEmpty(board_t board, int rank, char file) {
    if(board == NULL || !isRank(rank) || !isFile(file))
        return true;
    
    return board->data[rank - 1][(file - 'a') * 2] == ' ';
}
    
char pieceType (board_t board, int rank, char file) {
    if(board == NULL || !isRank(rank) || !isFile(file))
        return ' ';
        
    return board->data[rank - 1][(file - 'a') * 2 + 1];
}

bool isRank(int rank) {
    return rank >= 1 && rank < 1 + kNumRanks;
}

bool isFile(char file) {
    return file >= 'a' && file < 'a' + kNumFiles;
}

void setPiece(board_t board, bool isWhite, char type, int rank, char file) {
    if(board == NULL || type == ' ' || type == '\0' || !isRank(rank) || !isFile(file))
        return;
    
    char color = kBlackFlag;
    if(isWhite)
        color = kWhiteFlag;
    
    board->data[rank - 1][(file - 'a') * 2] = color;
    board->data[rank - 1][(file - 'a') * 2 + 1] = type;
}

void clearCell(board_t board, int rank, char file) {
    if(board == NULL || !isRank(rank) || !isFile(file))
        return;
        
    board->data[rank - 1][(file - 'a') * 2] = ' ';
    board->data[rank - 1][(file - 'a') * 2 + 1] = ' ';
}

void movePiece(board_t board, int srcRank, char srcFile, int destRank, char destFile) {
    if(board == NULL || !isRank(srcRank) || !isFile(srcFile) || !isRank(destRank) || !isFile(destFile))
        return;
    
    char color = board->data[srcRank - 1][(srcFile - 'a') * 2];
    char type = board->data[srcRank - 1][(srcFile - 'a') * 2 + 1];
    
    clearCell(board, srcRank, srcFile);
    board->data[destRank - 1][(destFile - 'a') * 2] = color;
    board->data[destRank - 1][(destFile - 'a') * 2 + 1] = type;
}

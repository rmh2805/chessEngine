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
    if(board == NULL)
        return false;
    
    return board->data[rank - 1][(file - 'a') * 2] == kWhiteFlag;
}

bool cellEmpty(board_t board, int rank, char file) {
    if(board == NULL)
        return true;
    
    return board->data[rank - 1][(file - 'a') * 2] == ' ';
}
    
char pieceType (board_t board, int rank, char file) {
    if(board == NULL)
        return ' ';
        
    return board->data[rank - 1][(file - 'a') * 2 + 1];
}

void setPiece(board_t board, bool isWhite, char type, int rank, char file) {
    if(board == NULL || type == ' ')
        return;
    
    char color = kBlackFlag;
    if(isWhite)
        color = kWhiteFlag;
    
    board->data[rank - 1][(file - 'a') * 2] = color;
    board->data[rank - 1][(file - 'a') * 2 + 1] = type;
}

void clearCell(board_t board, int rank, char file) {
    if(board == NULL)
        return;
        
    board->data[rank - 1][(file - 'a') * 2] = ' ';
    board->data[rank - 1][(file - 'a') * 2 + 1] = ' ';
}

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


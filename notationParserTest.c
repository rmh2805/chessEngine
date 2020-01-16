#define _DEFAULT_SOURCE

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "notationParser.h"
#include "chessDisp.h"
#include "chessBoard.h"
#include "chessGame.h"

#include "piece.h"

void cleanup(board_t board, char* buf) {
    if(board != NULL) {
        deleteBoard(board);
    }
    
    if(buf != NULL) {
        free(buf);
    }
}

void testMove(board_t board, char* buf, int srcRank, char srcFile, int destRank, char destFile) {
    bool goodMove = canMove(board, srcRank, srcFile, destRank, destFile);
    
    sprintf(buf, "%d%c->%d%c: %s\n", srcRank, srcFile, destRank, destFile, (goodMove)? "true" : "false");
    drawTurn(buf);
    
    if(goodMove) {
        movePiece(board, srcRank, srcFile, destRank, destFile);
        drawBoard(board);
    }
    
    getch();
}

int testMoveChecks() {
    board_t board = makeBoard();
    if(board == NULL) {
        fprintf(stderr, "Failed to allocate a board, exiting");
        return EXIT_FAILURE;
    }
    
    char* buf = calloc(45, sizeof(char));
    if(buf == NULL) {
        fprintf(stderr, "Failed to allocate a command buffer, exiting");
        cleanup(board, buf);
        return EXIT_FAILURE;
    }
    
    if(startDisp()) {
        fprintf(stderr, "Failed to start the display, exiting");
        cleanup(board, buf);
        return EXIT_FAILURE;
    }
    
    
   
    setPiece(board, false, kBishopFlag, 4, 'd');
    setPiece(board, false, kKingFlag, 8, 'h');
    setPiece(board, true, kKingFlag, 8, 'd');
    setPiece(board, true, kQueenFlag, 6, 'd');
    
    drawBoard(board);
    getch();
    
    testMove(board, buf, 4, 'd', 6, 'b');
    testMove(board, buf, 6, 'b', 8, 'd');
    testMove(board, buf, 6, 'd', 8, 'd');
    testMove(board, buf, 8, 'd', 8, 'h');
    
    
    stopDisp();
    deleteBoard(board);    
        
    return EXIT_SUCCESS;
}

void testNotationParse(board_t board, char* notation, bool isWhite) {
    char* result = notationToMove(board, notation, isWhite);
    
    printf("(%c) %s: ", (isWhite) ? 'W' : 'B', notation);
    if(result == NULL) {
        printf("Illegal move or failure in parse");
    }
    
    
    printf("\n");
}

int main (int argc, char**argv) {
    if(argc < 3) {
        fprintf(stderr, "Usage: %s <isWhite y/n> <Move to check>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    board_t board = makeBoard();
    if(board == NULL) {
        fprintf(stderr, "Failed to allocate the board\n");
        return EXIT_FAILURE;
    }
    
    
    startBoard(board);
    for(int i = 1; i < argc - 1; i += 2) {
        bool isWhite = argv[i][0] == 'y';
        testNotationParse(board, argv[i] + 1, isWhite);
    }
    
    
    printf("\nFinished Parsing\n\n");
    
    return EXIT_SUCCESS; 
}


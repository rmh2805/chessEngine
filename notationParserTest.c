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


const char* kCastle = "0-0";
const char* qCastle = "0-0-0";
const char* mate = "#";
const char* check = "+";

//======================<Misc Helper Functions>=======================//
void cleanup(board_t board, char* buf) {
    if(board != NULL) {
        deleteBoard(board);
    }
    
    if(buf != NULL) {
        free(buf);
    }
}

//======================<Base Tests>==================================//
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

void testNotationParse(board_t board, const char* notation, bool isWhite) {
    /*
     *  Standard: ['n', Source Rank, Source File, Dest Rank, Dest File]
     *  En passent: ['e', Source Rank, Source File, Dest Rank, Dest File]
     *  Queen-side castle: ['q']
     *  King-side castle: ['k']
     *  Check: ['c']
     *  Mate: ['m']
     *  Definitely Illegal: NULL
     */
    
    char* result = notationToMove(board, notation, isWhite);
    
    printf("(%c) %s: ", (isWhite) ? 'W' : 'B', notation);
    if(result == NULL) {
        printf("Illegal move or failure in parse\n");
        return;
    } 
    
    char flag = result[0];
    
    if(flag == 'q')
        printf("Successful Queen-Side Castle");
    else if (flag == 'k')
        printf("Successful King-Side Castle");
    else if (flag == 'c')
        printf("Check");
    else if (flag == 'm')
        printf("Mate");
    else if (flag == 'n')
        printf("Move from %c%d to %c%d", result[2], result[1], result[4], result[3]);
    else if (flag == 'e')
        printf("En Passent capture from %c%d to %c%d", result[2], result[1], result[4], result[3]);
    else
        printf("UNKNOWN RETURN");

    
    free(result);
    printf("\n");
}

void tryDispNotationParse(board_t board, const char* message) {
    if(!startDisp()) {
        drawBoard(board);
        drawTurn(message);
        getch();
        stopDisp();
    }
}

//======================<Multiple Tests>==============================//
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

void testCastlingParse() {
    board_t board = makeBoard();

    //======================<Success>======================//
    setPiece(board, false, kRookFlag, 8, 'a');
    setPiece(board, false, kRookFlag, 8, 'h');
    setPiece(board, false, kKingFlag, 8, 'e');
    
    setPiece(board, true, kRookFlag, 1, 'a');
    setPiece(board, true, kRookFlag, 1, 'h');
    setPiece(board, true, kKingFlag, 1, 'e');

    tryDispNotationParse(board, "Successful Castle Test Setup");
    
    printf("\n======================<Castle Success Tests>======================\n");
    testNotationParse(board, kCastle, true);
    testNotationParse(board, kCastle, false);
    testNotationParse(board, qCastle, true);
    testNotationParse(board, qCastle, false);
    fgetc(stdin);
    
    //======================<Failure>======================//
    setPiece(board, false, kKnightFlag, 8, 'b');
    setPiece(board, true, kKnightFlag, 1, 'g');
    
    tryDispNotationParse(board, "Unsuccessful Castle Test Setup");
    
    printf("\n======================<Castle Failure Tests>======================\n");
    testNotationParse(board, kCastle, true);
    testNotationParse(board, kCastle, false);
    testNotationParse(board, qCastle, true);
    testNotationParse(board, qCastle, false);
    fgetc(stdin);
    
    deleteBoard(board);
}

void testMiscParse() {
    board_t board = makeBoard();
    if(board == NULL)
        return;

    printf("\n======================<Misc Tests>================================\n");
    testNotationParse(board, check, true);
    testNotationParse(board, mate, true);

    deleteBoard(board);
}

void testPawnParse() {
    board_t board = makeBoard();
    if(board == NULL)
        return;

    startBoard(board);
    tryDispNotationParse(board, "Initial Pawn Setup");

    printf("\n======================<Pawn move Tests>================================\n");

    printf("Successes:\n");
    printf("Black Double advance: ");
    testNotationParse(board, "c6", false);
    printf("Black Single advance: ");
    testNotationParse(board, "d5", false);
    printf("White Single Advance: ");
    testNotationParse(board, "c3", true);
    printf("White Double Advance: ");
    testNotationParse(board, "d4", true);

    printf("Failures: \n");
    testNotationParse(board, "a8", false);
    testNotationParse(board, "b7", false);
    testNotationParse(board, "e4", false);
    testNotationParse(board, "a1", true);
    testNotationParse(board, "b2", true);
    testNotationParse(board, "e5", true);

    getch();


    setPiece(board, true, kPawnFlag, 5, 'a');
    setPiece(board, true, kPawnFlag, 4, 'b');
    setPiece(board, true, kPawnFlag, 5, 'c');
    setPiece(board, true, kPawnFlag, 6, 'g');
    setPiece(board, true, kPawnFlag, 4, 'e');

    
    setPiece(board, false, kPawnFlag, 4, 'a');
    setPiece(board, false, kPawnFlag, 5, 'b');
    setPiece(board, false, kPawnFlag, 4, 'c');
    setPiece(board, false, kPawnFlag, 3, 'g');
    setPiece(board, false, kPawnFlag, 5, 'f');

    
    tryDispNotationParse(board, "Secondary Testing Setup");

    
    printf("\n======================<En Passent Tests>===============================\n");
    printf("Success:\n");
    testNotationParse(board, "axb3", false);
    testNotationParse(board, "cxb3", false);
    testNotationParse(board, "axb6", true);
    testNotationParse(board, "cxb6", true);
    
    printf("\nFailure:\n");
    testNotationParse(board, "cxd6", true);
    testNotationParse(board, "cxb3", true);
    
    printf("\n======================<Capture Tests>==================================\n");
    printf("Success:\n");
    testNotationParse(board, "fxg3", true);
    testNotationParse(board, "hxg3", true);
    testNotationParse(board, "gxf7", true);
    testNotationParse(board, "gxh7", true);

    testNotationParse(board, "fxg6", false);
    testNotationParse(board, "hxg6", false);
    testNotationParse(board, "gxf2", false);
    testNotationParse(board, "gxh2", false);
    
    printf("\nFailure:\n");
    testNotationParse(board, "exg3", true);
    testNotationParse(board, "exf3", true);
    testNotationParse(board, "exg6", false);
    testNotationParse(board, "exf6", false);

    printf("\n======================<Misc Pawn Move Tests>===========================\n");
    printf("Block Move Fail Tests:\n");
    testNotationParse(board, "b5", true);
    testNotationParse(board, "b4", false);
    
    
    printf("\nDouble Advance Fail Tests:\n");
    testNotationParse(board, "e6", true);
    testNotationParse(board, "f3", false);

    printf("\nRetreat Fail Tests:\n");
    testNotationParse(board, "g5", true);
    testNotationParse(board, "g4", false);
        

    deleteBoard(board);
}

//======================<Main Function>===============================//
int main (int argc, char**argv) {
    if(argc >= 3) {
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
        
        deleteBoard(board);
        printf("\nFinished Parsing\n\n");
    
        return EXIT_SUCCESS; 
    }
    
    //======================<Preprogrammed Test>======================//
    testPawnParse();
    //testCastlingParse();
    //testMiscParse();
    
    return EXIT_SUCCESS; 
}


#include "notationParser.h"

const char standardMoveFlag = 'n';
const char queenCastleFlag = 'q';
const char kingCastleFlag = 'k';
const char checkFlag = 'c';
const char mateFlag = 'm';

char* parsePawn (board_t board, const char* move, bool whiteMove) {
	if(strlen(move) == 2) {
		//This is a simple move, no disambiguation ever needed. Format is just 'destFile''destRank'
	}
	
	if(strlen(move) >= 4) {
		//This is a pawn capture, possibly with en passent (CHECK). 'srcFile''x''destFile''destRank'
	}
	
	return NULL;
}

char* parseKing (board_t board, const char* move, bool whiteMove) {
	if(strlen(move) == 3) {
		//This is a simple move, no disambiguation 'K''destFile''destRank'
	}
	
	return NULL;
}

/**
 * Standard: ['n', Source Rank, Source File, Dest Rank, Dest File]
 * En passent: ['e', Source Rank, Source File, Dest Rank, Dest File]
 * Queen-side castle: ['q']
 * King-side castle: ['k']
 * Check: ['c']
 * Mate: ['m']
 * Definitely Illegal: NULL
 * All legal returns (except standard) must have further checks for legality, as they all have historical state dependancies
 * All legal returns must be freed by caller
 */
char* notationToMove (board_t board, const char * move, bool whiteMove) {
    if(board == NULL || move == NULL)
        return NULL;
        
    if(strlen(move) < 1)
		return NULL;
    
    char* toReturn = malloc(1 * sizeof(char));
    if(toReturn == NULL) 
		return NULL;
		
    //======================<Odd Parsing>=============================//
    if(move[0] == '+') {
		toReturn[0] = checkFlag;
		return toReturn;
	}
	
	if(move[0] == '#') {
		toReturn[0] = mateFlag;
		return toReturn;
	}
	
    if(strncmp("0-0", move, 3) == 0) {
        int startRank = (whiteMove) ? 1 : 8;
        
        const char kKingFile = 'e';
        char startFile, endFile, rookFile, returnFlag;
        
        if(pieceType(board, startRank, kKingFile) != kKingFlag || !colorMatch(board, startRank, kKingFile, whiteMove)) {
            //If the wrong piece (not the proper king) is in the king's square
            free(toReturn);
            return NULL;
        }
        
        
        if(strcmp("0-0", move) == 0) {
            //Check if king's castle is clear and (possibly) set
            startFile = 'f';
            endFile = 'g';
            rookFile = 'h';
            returnFlag = kingCastleFlag;
        }
        
        if(strcmp("0-0-0", move) == 0) {
            //Check if queen's castle is clear and (possibly) set
            startFile = 'b';
            endFile = 'd';
            rookFile = 'a';
            returnFlag = queenCastleFlag;
        }
        
        if(pieceType(board, startRank, rookFile) != kRookFlag || !colorMatch(board, startRank, rookFile, whiteMove)) {
            free(toReturn);
            return NULL;
        }
        
        for(char i = startFile; i <= endFile; i++) {
            if(!cellEmpty(board, startRank, i)) {
                free(toReturn);
                return NULL;
            }
        }
        
        toReturn[0] = returnFlag;
        return toReturn;
    }
	
	
    //======================<Check For Odd Pieces>====================//
    char pieceType = move[0];
    if(!pieceType) {
        free(toReturn);
		return parsePawn(board, move, whiteMove);
	} 
    
    if(pieceType == kKingFlag) {
        free(toReturn);
        return parseKing(board, move, whiteMove);
    }
	
    //======================<Check Standard Piece>====================//
	char moveLen = strlen(move);
	if(moveLen < 3)
		return NULL;
        
	toReturn = realloc(toReturn, 5 * sizeof(char));
	if(toReturn == NULL)
        return NULL;
    
    
    char srcRank = 0;
	char srcFile = 0;
	char destRank = move[moveLen - 1];
	char destFile = move[moveLen - 2];
	
	if(moveLen == 3) {
		//This is a simple move, no disambiguation ('R''destFile''destRank')
		//Do a full search on the board
		
	}
	
	if(strlen(move) == 4) {
		if(move[1] == 'x') {
			//This is a simple capture ('R''x''destFile''destRank')
			//Do a full search on the board
		} else {
			//This is a single disambiguation move ('R''srcFile/srcRank''destFile''destRank')
			//Do a search in the specified rank/file
		}
	}
	
	if(strlen(move) == 5) {
		if(move[2] == 'x') {
			//This is a simple capture ('R''srcFile/srcRank''x''destFile''destRank')
			//Do a search in the specified rank/file
		} else {
			//This is a single disambiguation move ('R''srcFile''srcRank''destFile''destRank')
			//src Given
		}
	}
	
	if(strlen(move) == 6) {
		//This is a doubly ambiguous capture ('R''srcFile''srcRank''x''destFile''destRank')
		//src Given
	}
	
	
	toReturn[0] = 'n';
	toReturn[1] = srcRank;
	toReturn[2] = srcFile;
	toReturn[3] = destRank;
	toReturn[4] = destFile;
	return toReturn;
}

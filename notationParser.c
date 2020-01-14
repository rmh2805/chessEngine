#include "notationParser.h"

char* parsePawn (board_t board, const char* move, bool whiteMove) {
	if(strlen(move) == 2) {
		//This is a simple move, no disambiguation ever needed. Format is just 'destFile''destRank'
	}
	
	if(strlen(move) >= 4) {
		//This is a pawn capture, possibly with en passent. 'srcFile''x''destFile''destRank'
	}
	
	return NULL;
}

char* parseRook (board_t board, const char* move, bool whiteMove) {
	char moveLen = strlen(move);
	if(moveLen < 3)
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
	
	char* toReturn = malloc(5 * sizeof(char));
	toReturn[0] = 'n';
	toReturn[1] = srcRank;
	toReturn[2] = srcFile;
	toReturn[3] = destRank;
	toReturn[4] = destFile;
	return NULL;
}
 
char* parseKnight (board_t board, const char* move, bool whiteMove) {
	if(strlen(move) == 3) {
		//This is a simple move, no disambiguation 'K''destFile''destRank'
	}
	
	return NULL;
}

char* parseBishop (board_t board, const char* move, bool whiteMove) {
	if(strlen(move) == 3) {
		//This is a simple move, no disambiguation 'B''destFile''destRank'
	}
	
	return NULL;
}

char* parseQueen (board_t board, const char* move, bool whiteMove) {
	if(strlen(move) == 3) {
		//This is a simple move, no disambiguation 'Q''destFile''destRank'
	}
	
	return NULL;
}

char* parseKing (board_t board, const char* move, bool whiteMove) {
	if(strlen(move) == 3) {
		//This is a simple move, no disambiguation 'K''destFile''destRank'
	}
	
	return NULL;
}

// Standard: ['n', Source Rank, Source File, Dest Rank, Dest File]
// En passent: ['e', Source Rank, Source File, Dest Rank, Dest File]
// Queen-side castle: ['q']
// King-side castle: ['k']
// Check: ['c']
// Mate: ['m']
// Definitely Illegal: NULL
// All legal returns (except standard) must have further checks for legality, as they all have historical state dependancies
// All legal returns must be freed by caller
char* notationToMove (board_t board, const char * move, bool whiteMove) {
    if(board == NULL || move == NULL)
        return NULL;
        
    if(strlen(move) < 1)
		return NULL;
    
    char* toReturn = malloc(1 * sizeof(char));
    if(toReturn == NULL) 
		return NULL;
		
    //==========================<Odd Parsing>=========================//
    if(move[0] == '+') {
		toReturn[0] = 'c';
		return toReturn;
	}
	
	if(move[0] == '#') {
		toReturn[0] = 'm';
		return toReturn;
	}
	
	if(strcmp("0-0", move) == 0) {
		//Check if king's castle is clear and (possibly) set
		toReturn[0] = 'k';
		return toReturn;
	}
	
	if(strcmp("0-0-0", move) == 0) {
		//Check if queen's castle is clear and (possibly) set
		toReturn[0] = 'q';
		return toReturn;
	}
	
	
	
    //==========================<Move Parsing>==========================//
    if(!isPiece(toReturn[0])) {
		return parsePawn(board, move, whiteMove);
	} 
	
	switch(toReturn[0]) {
	case kRookFlag:
		return parseRook(board, move, whiteMove);
	case kKnightFlag:
		return parseKnight(board, move, whiteMove);
	case kBishopFlag:
		return parseBishop(board, move, whiteMove);
	case kQueenFlag:
		return parseQueen(board, move, whiteMove);
	case kKingFlag:
		return parseKing(board, move, whiteMove);
		
	default:
		return NULL;
	}
    
    //MUST IMPLEMENT CHECKS FOR POSSIBILITY OF CHECK, MATE, EN PASSENT, 
    //AND CASTLING, AS WELL AS IF INITIAL STATE ALLOWS THEM IN THEORY. 
    //PIECE CHECKS DO NOT COVER THESE, AND WILL ONLY CHECK FOR STANDARD 
    //MOVEMENTS/CAPTURES 
}

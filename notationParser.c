#include "notationParser.h"


// Standard: ['n', Source Rank, Source File, Dest Rank, Dest File]
// En passent: ['e', Source Rank, Source File, Dest Rank, Dest File]
// Queen-side castle: ['q']
// King-side castle: ['k']
// Check: ['c']
// Mate: ['m']
// Definitely Illegal: NULL
// All legal returns (except standard) must have further checks for legality, as they all have historical state dependancies
char* notationToMove (board_t board, const char * move) {
    if(board == NULL || move == NULL)
        return NULL;
    
    //MUST IMPLEMENT CHECKS FOR POSSIBILITY OF CHECK, MATE, EN PASSENT, 
    //AND CASTLING, AS WELL AS IF INITIAL STATE ALLOWS THEM IN THEORY. 
    //PIECE CHECKS DO NOT COVER THESE, AND WILL ONLY CHECK FOR STANDARD 
    //MOVEMENTS/CAPTURES 


    return NULL;
}
 

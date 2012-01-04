#ifndef HUMAN_PLAYER_H_INCLUDED
#define HUMAN_PLAYER_H_INCLUDED

#include "chessplayer.h"

class ChessBoard;
class Move;

class HumanPlayer: public ChessPlayer {

	public:
	
		HumanPlayer(int color);
		
		~HumanPlayer();
		
		/*
		* Ask player what to do
		*/
		bool getMove(ChessBoard & board, Move & move) const;
		
		/*
		* Read input from stdin
		*/
		char * readInput(void) const;
		
		/*
		* Process input. Frees buffer allocated by readInput()
		*/
		bool processInput(char * buf, Move & move) const;

};

#endif

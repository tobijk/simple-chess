#ifndef HUMAN_PLAYER_H_INCLUDED
#define HUMAN_PLAYER_H_INCLUDED

#include "ChessPlayer.h"

class HumanPlayer: public ChessPlayer {

	public:
	
		HumanPlayer(int color);
		
		~HumanPlayer();
		
		/*
		* Ask player what to do
		*/
		bool getMove(ChessBoard & board, Move & move);
		
		/*
		* Read input from stdin
		*/
		char * readInput(void);
		
		/*
		* Process input. Frees buffer allocated by readInput()
		*/
		bool processInput(char * buf, Move & move);

};

#endif

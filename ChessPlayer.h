#ifndef CHESS_PLAYER_H_INCLUDED
#define CHESS_PLAYER_H_INCLUDED

#include "ChessBoard.h"

class ChessPlayer
{
	public:

		ChessPlayer(){};
		virtual ~ChessPlayer(){};
		
		/*
		* Ask player what to do next
		*/
		virtual bool getMove(ChessBoard & board, Move & move) = 0;

	protected:

		/*
		* Guess what...
		*/
		int color;
};

#endif

//#include <mcheck.h>
#include <cstdlib>
#include <cstdio>
#include "LinkedList.h"
#include "ChessBoard.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"

int main(void) {

	ChessBoard board;
	LinkedList<Move> regulars, nulls;
	ListIterator<Move> iter;
	int turn = WHITE;
	Move move;
	bool found;

	// Initialize players
	AIPlayer black(BLACK, 2);
	HumanPlayer white(WHITE);

	// setup board
	board.initDefaultSetup();

	do {
		// show board
		board.print();

		// query player's choice
		if(turn) {
			found = black.getMove(board, move);
		}
		else {
			found = white.getMove(board, move);
		}
		
		// if player has a move
		if(found) {
			
			// get all moves
			regulars.clear();
			nulls.clear();
			board.getMoves(turn, regulars, regulars, nulls);
			
			// execute maintenance moves
			iter = nulls.getIterator();
			while(*iter) {
				board.move((*iter)->value);
				iter++;
			}
			
			// execute move
			board.move(move);
			move.print();
		}

		// opponents turn
		turn = TOGGLE_COLOR(turn);
	}
	while(found);

	// who won?
	if(turn) {
		printf("\n   Black wins!\n\n");
	}
	else {
		printf("\n   White wins!\n\n");
	}
}

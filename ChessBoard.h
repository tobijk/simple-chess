#ifndef CHESS_BOARD_H_INCLUDED
#define CHESS_BOARD_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include "LinkedList.h"

// Pieces defined in lower 4 bits
#define EMPTY	0x00	// Empty square
#define PAWN	0x01	// Bauer
#define ROOK	0x02	// Turm
#define KNIGHT  0x03	// Springer
#define BISHOP  0x04	// Laeufer
#define QUEEN   0x05	// Koenigin
#define KING	0x06	// Koenig

// Extract figure's type
#define FIGURE(x) (0x0F & x)

// Attributes reside in upper 4 bits
#define SET_BLACK(x) (x | 0x10)
#define IS_BLACK(x)  (0x10 & x)

#define SET_MOVED(x) (x | 0x20)
#define IS_MOVED(x)  (0x20 & x)

// For pawn en passant candidates
#define SET_PASSANT(x)   (x | 0x40)
#define CLEAR_PASSANT(x) (x & 0xbf)
#define IS_PASSANT(x)    (0x40 & x)

// For pawn promotion
#define SET_PROMOTED(x)   (x | 0x80)
#define IS_PROMOTED(x)    (0x80 & x)
#define CLEAR_PROMOTED(x) (x & 0x7f)

// Constants to compare with the macros
#define WHITE 0x00
#define BLACK 0x10
#define TOGGLE_COLOR(x) (0x10 ^ x)

enum Position {
	A1 = 0, B1, C1, D1, E1, F1, G1, H1,
	A2, B2, C2, D2, E2, F2, G2, H2,
	A3, B3, C3, D3, E3, F3, G3, H3,
	A4, B4, C4, D4, E4, F4, G4, H4,
	A5, B5, C5, D5, E5, F5, G5, H5,
	A6, B6, C6, D6, E6, F6, G6, H6,
	A7, B7, C7, D7, E7, F7, G7, H7,
	A8, B8, C8, D8, E8, F8, G8, H8
};

struct Move
{
	/*
	* Prints sth. like "Black queen from D8 to D7."
	*/
	void print(void) {

		const char * field_name[] = {
			"A1", "B1", "C1", "D1", "E1", "F1", "G1", "H1",
			"A2", "B2", "C2", "D2", "E2", "F2", "G2", "H2",
			"A3", "B3", "C3", "D3", "E3", "F3", "G3", "H3",
			"A4", "B4", "C4", "D4", "E4", "F4", "G4", "H4",
			"A5", "B5", "C5", "D5", "E5", "F5", "G5", "H5",
			"A6", "B6", "C6", "D6", "E6", "F6", "G6", "H6",
			"A7", "B7", "C7", "D7", "E7", "F7", "G7", "H7",
			"A8", "B8", "C8", "D8", "E8", "F8", "G8", "H8"
		};		
	
		if(IS_BLACK(figure))
			printf("\n\n   Black ");
		else 
			printf("\n\n   White ");

		switch(FIGURE(figure)) {
			case PAWN:
				printf("pawn ");
				break;
			case ROOK:
				printf("rook ");
				break;
			case KNIGHT:
				printf("knight ");
				break;
			case BISHOP:
				printf("bishop ");
				break;
			case QUEEN:
				printf("queen ");
				break;
			case KING:
				printf("king ");
				break;
		}
		
		printf("from %s to %s:\n", field_name[(int)from], field_name[(int)to]);
	}
	
	bool operator==(Move & b) {
		if(from != b.from)
			return false;
		if(to != b.to)
			return false;
		if(capture != b.capture)
			return false;
		if(figure != b.figure)
			return false;
			
		return true;
	}

	char figure;	// figure which is moved
	char from, to;	// board is seen one-dimensional
	char capture;	// piece that resides at destination square
};

class ChessBoard
{
	public:

		ChessBoard();

		/*
		* Print ASCII representation of board.
		*/
		void print(void);

		/*
		* Returns an ASCII char representing the figure.
		*/
		char getASCIIrepr(int figure);

		/*
		* Initialize board for a normal game.
		*/
		void initDefaultSetup(void);

		/*
		* Generates all moves for one side.
		*/
		void getMoves(int color, LinkedList<Move> & moves, LinkedList<Move> & captures, LinkedList<Move> & null_moves);

		/*
		* All possible moves for a pawn piece.
		*/
		void getPawnMoves(int figure, int pos, LinkedList<Move> & moves, LinkedList<Move> & captures, LinkedList<Move> & null_moves);
		
		/*
		* All possible moves for a rook piece.
		*/
		void getRookMoves(int figure, int pos, LinkedList<Move> & moves, LinkedList<Move> & captures);
		
		/*
		* All possible moves for a knight piece.
		*/
		void getKnightMoves(int figure, int pos, LinkedList<Move> & moves, LinkedList<Move> & captures);
		
		/*
		* All possible moves for a bishop piece.
		*/
		void getBishopMoves(int figure, int pos, LinkedList<Move> & moves, LinkedList<Move> & captures);
		
		/*
		* All possible moves for a queen piece.
		*/
		void getQueenMoves(int figure, int pos, LinkedList<Move> & moves, LinkedList<Move> & captures);

		/*
		* All possible moves for a king piece.
		*/
		void getKingMoves(int figure, int pos, LinkedList<Move> & moves, LinkedList<Move> & captures);

		/*
		* Returns true, if this square is vulnerable to the opponent.
		* This is used to determine if castling is legal or if kings are in check.
		* En passant is not taken into account.
		*/
		bool isVulnerable(int pos, int color);

		/*
		* Move and undo moves
		*/
		void move(Move & move);
		void undoMove(Move & move);

		void movePawn(Move & move);
		void undoMovePawn(Move & move);

		void moveKing(Move & move);
		void undoMoveKing(Move & move);

		// THE BOARD ITSELF
		char square[8*8];

		// to keep track of the kings
		char black_king_pos;
		char white_king_pos;
};

#endif

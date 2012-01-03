#ifndef CHESS_BOARD_H_INCLUDED
#define CHESS_BOARD_H_INCLUDED

using namespace std;

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

struct Move
{
	/*
	* Prints sth. like "Black queen from D8 to D7."
	*/
	void print(void) const;
	
	/*
	* True if moves are equal.
	*/
	bool operator==(const Move & b) const;

	char figure;	// figure which is moved
	char from, to;	// board is seen one-dimensional
	char capture;	// piece that resides at destination square
};

class ChessBoard
{
	public:

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

		ChessBoard();

		/*
		* Print ASCII representation of board.
		*/
		void print(void) const;

		/*
		* Returns an ASCII char representing the figure.
		*/
		char getASCIIrepr(int figure) const;

		/*
		* Initialize board for a normal game.
		*/
		void initDefaultSetup(void);

		/*
		* Generates all moves for one side.
		*/
		void getMoves(int color, list<Move> & moves, list<Move> & captures, list<Move> & null_moves);

		/*
		* All possible moves for a pawn piece.
		*/
		void getPawnMoves(int figure, int pos, list<Move> & moves, list<Move> & captures, list<Move> & null_moves) const;
		
		/*
		* All possible moves for a rook piece.
		*/
		void getRookMoves(int figure, int pos, list<Move> & moves, list<Move> & captures) const;
		
		/*
		* All possible moves for a knight piece.
		*/
		void getKnightMoves(int figure, int pos, list<Move> & moves, list<Move> & captures) const;
		
		/*
		* All possible moves for a bishop piece.
		*/
		void getBishopMoves(int figure, int pos, list<Move> & moves, list<Move> & captures) const;
		
		/*
		* All possible moves for a queen piece.
		*/
		void getQueenMoves(int figure, int pos, list<Move> & moves, list<Move> & captures) const;

		/*
		* All possible moves for a king piece.
		*/
		void getKingMoves(int figure, int pos, list<Move> & moves, list<Move> & captures);

		/*
		* Returns true, if this square is vulnerable to the opponent.
		* This is used to determine if castling is legal or if kings are in check.
		* En passant is not taken into account.
		*/
		bool isVulnerable(int pos, int color) const;

		/*
		* Move and undo moves
		*/
		void move(const Move & move);
		void undoMove(const Move & move);

		void movePawn(const Move & move);
		void undoMovePawn(const Move & move);

		void moveKing(const Move & move);
		void undoMoveKing(const Move & move);

		// THE BOARD ITSELF
		char square[8*8];

		// to keep track of the kings
		char black_king_pos;
		char white_king_pos;
};

#endif

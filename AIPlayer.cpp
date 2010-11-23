#include "AIPlayer.h"

bool AIPlayer::getMove(ChessBoard & board, Move & move)
{
	LinkedList<Move> regulars, nulls, candidates;
	ListIterator<Move> iter;
        bool quiescent = false;
	int best, tmp;

	// first assume we are loosing
	best = -KING_VALUE;
	
	// get all moves
	board.getMoves(this->color, regulars, regulars, nulls);

	// execute maintenance moves
	iter = nulls.getIterator();
	while(*iter) {
		board.move((*iter)->value);
		iter++;
	}

	// loop over all moves
	iter = regulars.getIterator();
	while(*iter) {

		// execute move
		board.move((*iter)->value);

		// check if own king is vulnerable now
		if(!board.isVulnerable((this->color ? board.black_king_pos : board.white_king_pos), this->color)) {

			if(((*iter)->value).capture != EMPTY) {
                            quiescent = true;
			}

			// recursion
			tmp = -evalAlphaBeta(board, TOGGLE_COLOR(this->color), this->search_depth - 1, -WIN_VALUE, -best, quiescent);
			if(tmp > best) {
				best = tmp;
				candidates.clear();
				candidates.append((*iter)->value);
			}
			else if(tmp == best) {
				candidates.append((*iter)->value);
			}
		}

		// undo move and inc iterator
		board.undoMove((*iter)->value);
		iter++;
	}

	// undo maintenance moves
	iter = nulls.getIterator();
	while(*iter) {
		board.undoMove((*iter)->value);
		iter++;
	}

	// loosing the game?
	if(best < -WIN_VALUE) {
		return false;
	}
	else {
		// select random move from candidate moves
		move = candidates.getItem(rand() % candidates.getSize())->value;
		return true;
	}
}


int AIPlayer::evalAlphaBeta(ChessBoard & board, int color, int search_depth, int alpha, int beta, bool quiescent)
{
	LinkedList<Move> regulars, nulls;
	ListIterator<Move> iter;
	int best, tmp;

	if(search_depth <= 0 && !quiescent) {
		if(color)
			return -evaluateBoard(board);
		else
			return +evaluateBoard(board);
	}

	// first assume we are loosing
	best = -WIN_VALUE;

	// get all moves
	board.getMoves(color, regulars, regulars, nulls);
	
	// execute maintenance moves
	iter = nulls.getIterator();
	while(*iter) {
		board.move((*iter)->value);
		iter++;
	}
	
	// loop over all moves
	iter = regulars.getIterator();
	while((*iter) && (alpha <= beta)) {

		// execute move
		board.move((*iter)->value);

		// check if own king is vulnerable now
		if(!board.isVulnerable((color ? board.black_king_pos : board.white_king_pos), color)) {

			if(((*iter)->value).capture == EMPTY) {
                            quiescent = false;
			}
                        else {
                            quiescent = true;
                        }

			// recursion 'n' pruning
			tmp = -evalAlphaBeta(board, TOGGLE_COLOR(color), search_depth - 1, -beta, -alpha, quiescent);
			if(tmp > best) {
				best = tmp;
				if(tmp > alpha) {
					alpha = tmp;
				}
			}
		}

		// undo move and inc iterator
		board.undoMove((*iter)->value);
		iter++;
	}
	
	// undo maintenance moves
	iter = nulls.getIterator();
	while(*iter) {
		board.undoMove((*iter)->value);
		iter++;
	}
	
	return best;
}

int AIPlayer::evalMinMax(ChessBoard & board, int color, int search_depth)
{
	LinkedList<Move> regulars, nulls;
	ListIterator<Move> iter;
	int best, tmp;

	if(search_depth <= 0) {
		if(color)
			return -evaluateBoard(board);
		else
			return +evaluateBoard(board);
	}

	// first assume we are loosing
	best = -WIN_VALUE;

	// get all moves
	board.getMoves(color, regulars, regulars, nulls);
	
	// execute maintenance moves
	iter = nulls.getIterator();
	while(*iter) {
		board.move((*iter)->value);
		iter++;
	}
	
	// loop over all moves
	iter = regulars.getIterator();
	while(*iter) {

		// execute move
		board.move((*iter)->value);

		// check if own king is vulnerable now
		if(!board.isVulnerable((color ? board.black_king_pos : board.white_king_pos), color)) {

			// recursion
			tmp = -evalMinMax(board, TOGGLE_COLOR(color), search_depth - 1);
			if(tmp > best) {
				best = tmp;
			}
		}

		// undo move and inc iterator
		board.undoMove((*iter)->value);
		iter++;
	}
	
	// undo maintenance moves
	iter = nulls.getIterator();
	while(*iter) {
		board.undoMove((*iter)->value);
		iter++;
	}
	
	return best;
}

int AIPlayer::evaluateBoard(ChessBoard & board)
{
	int figure, pos, sum = 0, summand;

	for(pos = 0; pos < 64; pos++)
	{
		figure = board.square[pos];
		switch(FIGURE(figure))
		{
			case PAWN:
				summand = PAWN_VALUE;
				break;
			case ROOK:
				summand = ROOK_VALUE;
				break;
			case KNIGHT:
				summand = KNIGHT_VALUE;
				break;
			case BISHOP:
				summand = BISHOP_VALUE;
				break;
			case QUEEN:
				summand = QUEEN_VALUE;
				break;
			case KING:
				summand = KING_VALUE;
				break;
			default:
				summand = 0;
				break;
		}
		
		sum += IS_BLACK(figure) ? -summand : summand;
	}
	
	return sum;
}

#include "BigBoard.h"

namespace ttt {

	BigBoard::BigBoard() :
		hasWin( false ),
		hasTie( false ),
		starter( '\0' ),
		mover  ( '\0' ),
		winner ( '\0' )
	{
		allocateBoards();
	}

	void BigBoard::allocateBoards() {
		boards[0] = new Board();
		boards[1] = new Board();
		boards[2] = new Board();
		boards[3] = new Board();
		boards[4] = new Board();
		boards[5] = new Board();
		boards[6] = new Board();
		boards[7] = new Board();
		boards[8] = new Board();
	}

	bool BigBoard::subBoardHasWin( int board ) {
		return boards[board]->hasWin();
	}

	bool BigBoard::subBoardHasTie( int board ) {
		return boards[board]->hasTie();
	}

	char BigBoard::subBoardWinner( int board ) {
		return boards[board]->getWinner();
	}

	void BigBoard::move( int board, char sym, int col, int row ) {
		boards[board]->move( sym, col, row );
	}

	char BigBoard::intSymbolAt( int board, int square ) {
		return boards[board]->intSymbolAt( square );
	}

	void BigBoard::subBoardCharRepr( int board, char* repr ) {
		for ( int i=0; i<3; i++ ) {
			for ( int j=0; j<3; j++ ) {
				repr[ (i*3) + j ] = boards[board]->symbolAt(j, i);
			}
		}
	}

} // namespace ttt


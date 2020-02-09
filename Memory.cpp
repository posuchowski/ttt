#include <iostream>
#include "Memory.h"

namespace ttt {

	Memory::MemCell::MemCell() : score(0), moveNum(1), previous(nullptr) {
		for ( int i=0; i<9; i++ ) nextMove[i] = nullptr;
	}

	// FIXME: Option to pass *Val as param
  Memory::Memory() :
		lastMove(-1),
		rootCell(new MemCell),
		movePtr(rootCell),
		winVal(1),
		lossVal(-1),
		tieVal(0)
	{ }

	void * Memory::getRootCellAddr() {
		return (void *)rootCell;
	}

	void * Memory::getMovePtr() {
		return (void *)movePtr;
	}

	void Memory::resetMovePtr() {
		movePtr = rootCell;
	}

	// FIXME: Throw exception instead??
	void Memory::retreat() {
		if ( movePtr->previous != nullptr )
			movePtr = movePtr->previous;
	}

	void Memory::advance(int mv) {
		if ( doesRemember(mv) );
		else {
			movePtr->nextMove[mv] = new MemCell;
			movePtr->nextMove[mv]->moveNum  = (movePtr->moveNum)+1;
			movePtr->nextMove[mv]->previous = movePtr;
		}
		movePtr = movePtr->nextMove[mv];
		lastMove = mv;
	}

	bool Memory::doesRemember(int mv) {
		if ( movePtr->nextMove[mv] != nullptr )
			return true;
		return false;
	}

	int Memory::getMovePtrMove() {
		if ( movePtr->previous != nullptr ) {
			for ( int i=0; i<9; i++ ) {
				if ( movePtr->previous->nextMove[i] == movePtr )
					return i;
			}
		}
		return -1;  // at empty board
	}

	int Memory::scoreMove(int mv) {
		if ( doesRemember(mv) )
			return movePtr->nextMove[mv]->score;
		return 0;
	}

	void Memory::backPropagate(int val1, int val2) {
		int val = val1;
		do {
			movePtr->score += (val * movePtr->moveNum);
			// std::cerr << "Memory: setting cell " << movePtr << " to " << movePtr->score << std::endl;
			if ( val == val1 ) 
				val = val2;
			else
				val = val1;
			retreat();
		} while ( movePtr->previous != nullptr );
		// movePtr->score += val;
	}

	void Memory::rememberWin() {
		if ( winVal != 0 ) backPropagate(winVal, lossVal);
	}

	void Memory::rememberLoss() {
		if ( lossVal != 0 ) backPropagate(lossVal, winVal);
	}

	void Memory::rememberTie() {
		;
	}

}


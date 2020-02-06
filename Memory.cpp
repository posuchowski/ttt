#include <iostream>
#include "Memory.h"

namespace ttt {

	Memory::MemCell::MemCell() : previous(nullptr), score(0) {
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
		std::cerr << "resetMovePtr: movePtr to rootCell at " << movePtr << std::endl;
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
			std::cerr << "advance: Created new node " << movePtr->nextMove[mv] << " for move " << mv << std::endl;
			movePtr->nextMove[mv]->previous = movePtr;
		}
		movePtr = movePtr->nextMove[mv];
		std::cerr << "advance: For move " << mv << " moving ptr to node " << movePtr << std::endl;
		lastMove = mv;
	}

	bool Memory::doesRemember(int mv) {
		if ( movePtr->nextMove[mv] != nullptr )
			return true;
		std::cerr << "doesRemember: " << movePtr << " does NOT remember move " << mv << std::endl;
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
		if ( doesRemember(mv) ) {
			std::cerr << "scoreMove: move " << mv << " is remembered in node " << movePtr << std::endl;
			int s = movePtr->nextMove[mv]->score;
			std::cerr << "scoreMove: and its score is " << s << std::endl;
			return movePtr->nextMove[mv]->score;
		}
		std::cerr << "scoreMove: Returning 0 for node " << movePtr->nextMove[mv] << " instead of " << movePtr->nextMove[mv]->score << std::endl;
		return 0;
	}

	void Memory::backPropagate(int val) {
		do {
			std::cerr << "backPropagate: adding " << val << " to " << movePtr << std::endl;
			movePtr->score += val;
			retreat();
		}
		while ( movePtr->previous != nullptr );
		std::cerr << "backPropagate: adding " << val << " to " << movePtr << std::endl;
		movePtr->score += val;
	}

	void Memory::rememberWin() {
		if ( winVal != 0 ) backPropagate(winVal);
	}

	void Memory::rememberLoss() {
		if ( lossVal != 0 ) backPropagate(lossVal);
	}

	void Memory::rememberTie() {
		if ( tieVal != 0 ) backPropagate(tieVal);
	}

}


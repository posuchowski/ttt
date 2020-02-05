#include <iostream>
#include "Memory.h"

namespace ttt {

	Memory::MemCell::MemCell() : previous(nullptr), score(0) {
		for ( int i=0; i<9; i++ ) nextMove[i] = nullptr;
	}

  Memory::Memory() :
		lastMove(-1),
		rootCell(new MemCell),
		movePtr(rootCell)
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

}

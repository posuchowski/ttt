#include "MemCell.h"

namespace ttt {

	void MemCell::setScore( int ) { score = int;  }
	int  MemCell::getScore()      { return score; }

	void MemCell::setMove( int ) { move = int;  }
	int  MemCell::getMove()      { return move; }
	
	bool MemCell::addMove( MemCell * m ) {
		if ( nextMove[m->move] != nullptr )
			return false;
		nextMove[m->move] = m;
		return true;
	}

}

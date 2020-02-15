#include <iostream>
#include "BigBoard.h"
#include "Move.h"

using std::cout;
using std::cerr;
using std::endl;

ttt::BigBoard * BB = nullptr;

TEST_CASE( "Instantiate BigBoard", "[bigboard]" ) {
	cout << "\n===== EXERCISING BigBoard =====\n" << endl;
	BB = new ttt::BigBoard();
	cout << "Created new BigBoard!" << endl;
}

TEST_CASE( "Make a move on each board.", "[bigboard]" ) {
	Move moves[9] = {
		{ 0, 'X', 0, 0 },
		{ 1, 'O', 0, 1 },
		{ 2, 'X', 0, 2 },
		{ 3, 'O', 1, 0 },
		{ 4, 'X', 1, 1 },
		{ 5, 'O', 1, 2 },
		{ 6, 'X', 2, 0 },
		{ 7, 'O', 2, 1 },
		{ 8, 'X', 2, 2 }
	};
	for ( int i=0; i<9; i++ ) {
		BB->move(
			moves[i].board,
			moves[i].symbol,
			moves[i].col,
			moves[i].row
		);
		REQUIRE(
			BB->intSymbolAt( moves[i].board, moves[i].col + (moves[i].row * 3)) == moves[i].symbol
		);
	}
	cout << "OK, Made moves on all 9 boards." << endl;
}


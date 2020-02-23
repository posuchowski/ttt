#include <iostream>
#include <string>
#include <catch2/catch.hpp>
#include "Board.h"

ttt::Board * board = nullptr;

TEST_CASE( "Instantiate Board", "[board]" ) {
	std::cout << "\n===== EXERCISING BOARD =====\n" << std::endl;
	board = new ttt::Board( 0, 0 );
	REQUIRE( board != nullptr );
	std::cout << "Created new Board object." << std::endl;
}

TEST_CASE( "Set board directly and check row wins", "[board]" ) {
	// ttt::Board * newboard = new ttt::Board;

	int test_boards_x[] = {
			1+2+4, 8+16+32, 64+128+256
	};
	int test_boards_o[] = {
			8+16+256, 1+4+64, 8+2+4
	};

	for ( int i=0; i<3; i++ ) {
		board->clear();
		board->set_X(test_boards_x[i]);
		board->set_O(test_boards_o[i]);
		std::cout << "BOARD: " << board->toString() << std::endl;
		CHECK( board->hasWin() );
		REQUIRE( board->getWinner() == 'X' );
		std::cout << "X won with x repr " << board->get_X() << std::endl;
	}
}

TEST_CASE( "Set board directly and check column wins", "[board]" ) {

	int test_boards_o[] = {
		1+8+64, 2+16+128, 4+32+256
	};
	int test_boards_x[] = {
		2+16, 256+64, 1+16
	};

	for ( int i=0; i<3; i++ ) {
		board->clear();
		board->set_X(test_boards_x[i]);
		board->set_O(test_boards_o[i]);
		std::cout << "BOARD: " << board->toString() << std::endl;
		CHECK( board->hasWin() );
		REQUIRE( board->getWinner() == 'O' );
		std::cout << "O won with o repr " << board->get_O() << std::endl;
	}
}

TEST_CASE( "Test 0-8 diagonal win", "[board]" ) {
	board->clear();
	board->set_X(4+32);
	board->set_O(1+16+256);
	std::cout << "BOARD: " << board->toString() << std::endl;
	CHECK( board->hasWin() );
	REQUIRE( board->getWinner() == 'O' );
	std::cout << "O won with o repr " << board->get_O() << std::endl;
}

TEST_CASE( "Test 2-6 diagonal win", "[board]" ) {
	board->clear();
	board->set_X(4+16+64);
	board->set_O(1+2);
	std::cout << "BOARD: " << board->toString() << std::endl;
	CHECK( board->hasWin() );
	REQUIRE( board->getWinner() == 'X' );
	std::cout << "X won with x repr " << board->get_X() << std::endl;
}

TEST_CASE( "Test col, row moves", "[board]" ) {
	using Catch::Matchers::Contains;
	struct Move {
		char sym;
		int col, row;
	};
	Move moves[4] = {
		{ 'X', 1, 0 },
		{ 'O', 1, 1 },
		{ 'X', 0, 2 },
		{ 'O', 2, 2 }
	};
	for ( int i=0; i<4; i++ ) {
		board->clear();
		board->setStarter( moves[i].sym );
		CHECK_THROWS_WITH(
			board->setStarter( moves[i].sym ),
			Contains( "Board::setStarter" ) && Contains( "already set" )
		);
		board->move( moves[i].sym, moves[i].col, moves[i].row );
		std::cout << "BOARD: " << board->toString() << std::endl;
		CHECK( board->isOccupied( moves[i].col, moves[i].row ) );
		REQUIRE( board->symbolAt( moves[i].col, moves[i].row ) == moves[i].sym );
		std::cout << moves[i].sym << " is at col: " << moves[i].col << " row: "
			<< moves[i].row << std::endl;
		REQUIRE( board->getMover() != moves[i].sym );
		std::cout << "Next to move is: " << board->getMover() << std::endl;
  }
}

TEST_CASE( "Check full with tie", "[board]" ) {
	/*
   *   X | O | X
   *   ----------
   *   O | O | X
   *   ----------
   *   X | X | O
   */
	struct Move {
		char sym;
		int col, row;
	} moves[9] = {
		{ 'X', 0, 0 }, { 'O', 1, 0 },
		{ 'X', 2, 0 }, { 'O', 0, 1 },
		{ 'X', 2, 1 }, { 'O', 1, 1 },
		{ 'X', 0, 2 }, { 'O', 2, 2 },
		{ 'X', 1, 2 }
	};
	board->clear();
	for ( int i=0; i<9; i++ ) {
		board->move( moves[i].sym, moves[i].col, moves[i].row );
	}
	std::cout << "BOARD: " << board->toString() << std::endl;
	REQUIRE( board->hasWin() == false );
	REQUIRE( board->isFull() == true  );
	REQUIRE( board->hasTie() == true  );
}

TEST_CASE( "Check if toString representation is correct", "[board]" ) {
	std::string reprFromPreviousTest = "XOXOOXXXO";
	REQUIRE( board->toString() == reprFromPreviousTest );
}



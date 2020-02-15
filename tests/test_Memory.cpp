#include <iostream>
#include <catch2/catch.hpp>
#include "Memory.h"

ttt::Memory * memory = nullptr;

TEST_CASE( "Instantiate Memory", "[memory]" ) {
	std::cerr << "\n===== EXERCISING MEMORY =====\n" << std::endl;
	memory = new ttt::Memory;
	REQUIRE( memory != nullptr );
	std::cerr << "Memory instantiated OK" << std::endl;
}

TEST_CASE( "Move pointer points to root cell", "[memory]" ) {
	REQUIRE( memory->getRootCellAddr() == memory->getMovePtr() );
	std::cerr << "Root = " << memory->getRootCellAddr() << "; Move = " << memory->getMovePtr() << std::endl;
}

TEST_CASE( "Make integer move", "[memory]" ) {
	memory->advance(3);
	REQUIRE( memory->getRootCellAddr() != memory->getMovePtr() );
	std::cerr << "Moved 3, advancing move pointer to " << memory->getMovePtr() << std::endl;
}

TEST_CASE( "Do we NOT remember moving 2?", "[memory]" ) {
	memory->resetMovePtr();
	REQUIRE( ! memory->doesRemember(2) );
	std::cerr << "Memory does NOT remember move to 2 (Good)." << std::endl;
}

TEST_CASE( "Do we remember moving 3?", "[memory]" ) {
	memory->resetMovePtr();
	REQUIRE( memory->doesRemember(3) );
	std::cerr << "Memory doesRemember first move to 3" << std::endl;
}

ttt::Memory * newmem = nullptr;
int moves [5] = { 0, 2, 4, 7, 8 };

TEST_CASE( "Create new memory", "[memory]" ) {
	newmem = new ttt::Memory;
	std::cerr << "Root = " << newmem->getRootCellAddr() << "; Move = " << newmem->getMovePtr() << "\n" << std::endl;
	REQUIRE( newmem != memory );
}

TEST_CASE( "Play several moves", "[newmem]" ) {
	std::cerr << std::endl << "Playing some moves..." << std::endl;
	for ( int i=0; i<5; i++ ) {
		newmem->advance(moves[i]);
		std::cerr << "\t" << moves[i] << std::endl;
	}
	newmem->resetMovePtr();
	std::cerr << "Reset movePtr to " << newmem->getMovePtr() << std::endl;
	for ( int i=0; i<5; i++ ) {
		REQUIRE( newmem->doesRemember(moves[i]) );
		newmem->advance(moves[i]);
		std::cerr << "We remember " << moves[i] << std::endl;
	}
}

TEST_CASE( "Backpropagate score", "[memory]" ) {
	newmem->rememberWin();
	REQUIRE( newmem->getMovePtr() == newmem->getRootCellAddr() );
}

/* FIXME: Scoring algorithm has changed
TEST_CASE( "Remember win" ) {
	for ( int i=0; i<5; i++ ) {
		std::cerr << "Checking score for move " << moves[i] << std::endl;
		REQUIRE( newmem->scoreMove(moves[i]) == 1 );
		std::cerr << "OK: " << moves[i] << " scored 1" << std::endl;
		newmem->advance(moves[i]);
	}
	std::cerr << std::endl;
}
*/


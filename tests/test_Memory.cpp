#include <iostream>
#include <catch2/catch.hpp>
#include "Memory.h"

ttt::Memory * memory = nullptr;

TEST_CASE( "Instantiate Memory", "[memory]" ) {
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


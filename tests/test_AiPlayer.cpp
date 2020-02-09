#include <iostream>
#include <catch2/catch.hpp>
#include "AiPlayer.h"

ttt::AiPlayer * player = nullptr;
ttt::Board * aiboard = new ttt::Board;

TEST_CASE( "Instantiate AI player", "[ai]" ) {
	std::cout << "\n===== EXERCISING AI PLAYER =====\n" << std::endl;
	player = new ttt::AiPlayer;
	REQUIRE( player != nullptr );
	std::cout << "Created new AI player object." << std::endl;
}

TEST_CASE( "Collect empty squares on non-empty board", "[ai]" ) {
	using std::vector;
	int filled[] = { 0, 2, 4, 6, 8 };
	int empty[]  = { 1, 3, 5, 7 };

	for ( int i=0; i<5; i++ ) {
		aiboard->intMove('O', filled[i]);
		std::cout << "Filled square " << filled[i] << std::endl;
	}

	player->collectEmptySquares(aiboard);
	const vector<ttt::AiMove *> & moves = player->getPossibleMoves();
	player->dumpPossibleMoves();
	for ( int i=0; i<4; i++ ) {
		CHECK( moves[i]->move == empty[i] );
		std::cout << empty[i] << " was collected as empty" << std::endl;
	}
}

TEST_CASE( "Get a move on previous board", "[ai]" ) {
	int filled[] = { 0, 2, 4, 6, 8 };
	int m = player->makeMove(aiboard);
	for ( int i=0; i<5; i++ ) {
		REQUIRE_FALSE( m == filled[i] );
	}
	std::cerr << "AiPlayer moved to empty cell: " << m << std::endl;
}

TEST_CASE( "Get another move later", "[ai]" ) {
	aiboard->intMove('X', 1);
	int m = player->makeMove(aiboard);
	REQUIRE_FALSE( m == 1 );
	std::cerr << "AiPlayer moved to empty cell: " << m << std::endl;
}


#include <stdexcept>
#include <iostream>
#include "ConsoleUI.h"

namespace ttt {

	using std::cout;
	using std::cin;
	using std::cerr;
	using std::endl;

	ConsoleUI::ConsoleUI() : moveBoard(-1) { }

	void ConsoleUI::startGame() {
		cout << "Welcome to uTTT: Ultimate Tic Tac Toe!\n" << endl;
	}

	char ConsoleUI::getHumanSymbol() {
		char symbol = '\0';
		do {
			cout << "Please choose your symbol.\nEnter X or O: ";
			cin >> symbol;
			cout << "\n" << endl;
		} while ( (symbol != 'X') && (symbol != 'O') );
		return symbol;
	}

	int ConsoleUI::getMoveBoard() {
		char board = 0;
		do {
			cout << "Enter board [1-9]: ";
			cin >> board;
			cout << "\n" << endl;
		} while ( (board < 1) || (board > 9) );
		return board;
	}

	int ConsoleUI::getHumanMove() {
		int move = 0;
		do {
			cout << "Enter square [1-9]: ";
			cin >> move;
			cout << "\n" << endl;
		} while ( (move < 1) || (move > 9) );
		return (move - 1);
	}

	void ConsoleUI::updateDisplay( BigBoard * ) {
		throw std::runtime_error( "Unimplemented" );
	}

	void ConsoleUI::updateStats( int win, int loss, int draw ) {
		cout << "Statistics: WINS: " << win << " LOSSES: " << loss;
		cout << " TIES: " << draw << endl << endl;
	}

	void ConsoleUI::printOneBoard(Board * board) {
		cout << endl;
		for (int r = 0; r<3; ++r) {
			cout << "\t";
			for ( int c = 0; c<3; ++c ) {
				(bool)(( board->get_X() >> (r*3+c) ) & 1)
					? cout << " X "
					: (bool)(( board->get_O() >> (r*3+c) ) & 1 )
						? cout << " O "
						: cout << "   ";
				(bool)( ~c & 2 ) ? cout << "|" : cout << endl;
			}
			(bool)( ~r & 2 ) ? cout << "\t-----------" << endl : cout << endl;
		}
	}

	void ConsoleUI::onGameWon(int gameNum) {
		cout << "You won game " << gameNum << "!\n";		
	}

	void ConsoleUI::onGameLost(int gameNum) {
		cout << "You lost game " << gameNum << endl;		
	}

	void ConsoleUI::onGameTied(int gameNum) {
		cout << "You tied game " << gameNum << endl;
	}

	void ConsoleUI::goodBye() {
		cout << "\nThanks for playing. Goodbye.\n" << endl;
	}

} // namespace ttt


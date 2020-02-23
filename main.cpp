#include <iostream>
#include <stdlib.h>

#include "Board.h"
#include "ConsoleUI.h"
#include "AiPlayer.h"

using namespace ttt;

struct Pieces {
	char computer, human;
};

struct Statistics {
	int wins;
	int losses;
	int ties;
};

int gameLoop( ConsoleUI*, Pieces&, AiPlayer*, char );
void print_statistics( Statistics & );

int main() {

		Statistics stats   = { 0, 0, 0 };
    Pieces     symbols = { 'X', 'O' };

		ConsoleUI * UI = new ConsoleUI;
		AiPlayer * cplayer = new AiPlayer;

		symbols.human    = UI->getHumanSymbol();
		symbols.computer = ( symbols.human == 'X' ) ? 'O' : 'X';
		char starter     = symbols.human;

		while ( true ) {

			int result = gameLoop( UI, symbols, cplayer, starter );

			if ( result == 1 )
				stats.wins += 1;
			else if ( result == -1 )
				stats.losses += 1;
			else
				stats.ties += 1;	
			UI->updateStats( stats.wins, stats.losses, stats.ties );

			if ( starter == 'X' )
				starter = 'O';
			else
				starter = 'X';
		}

		UI->goodBye();
    return 0;
}

int gameLoop( ConsoleUI * UI, Pieces & symbols, AiPlayer * cplayer, char starter ) {

    Board * board = new Board;
		board->setStarter( starter );

		UI->startGame();
		cplayer->onNewGame();
    while ( true ) {
				if ( symbols.human == starter ) {
					UI->printOneBoard( board );
					int humanMove = UI->getHumanMove();
					board->intMove( symbols.human, humanMove );
					if ( board->hasWin() or board->isFull() )
						break;
					board->intMove( symbols.computer, cplayer->makeMove(board) );
					if ( board->hasWin() or board->isFull() )
						break;
				}
				else {
					board->intMove( symbols.computer, cplayer->makeMove(board) );
					if ( board->hasWin() or board->isFull() )
						break;
					UI->printOneBoard( board );
					int humanMove = UI->getHumanMove();
					board->intMove( symbols.human, humanMove );
					if ( board->hasWin() or board->isFull() )
						break;
				}
    }
		UI->printOneBoard( board );
		if ( board->hasWin() ) {
			if ( board->getWinner() == symbols.human ) {
					UI->onGameWon(0);
					cplayer->onLoss();
					return 1;
			}
			else if ( board->getWinner() == symbols.computer ) {
					UI->onGameLost(0);
					cplayer->onWin();
					return -1;
			}
		}
		// not hasWin but isFull == tie
		if ( board->isFull() ) {
				UI->onGameTied(0);
				cplayer->onTie();
				return 0;
		}
		return 0;
}


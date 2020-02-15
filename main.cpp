#include <iostream>
#include <stdlib.h>
#include "Board.h"
#include "AiPlayer.h"

using namespace ttt;

using std::cout;
using std::cerr;
using std::cin;
using std::endl;

struct Pieces {
	char computer, human;
};
struct Statistics {
	int wins, losses, ties;
};

const char * clearCmd = "clear";

int gameLoop( Pieces &, AiPlayer *, char );
void getSymbols( Pieces & );
int getHumanMove( Board * );
void print_statistics( Statistics & );

int main() {

    Pieces symbols = { 'X', 'O' };
		Statistics stats = { 0, 0, 0 };
		AiPlayer * cplayer = new AiPlayer;

    getSymbols( symbols );
		char starter = 'X';

		while ( true ) {

			int result = gameLoop( symbols, cplayer, starter );

			if ( result == 1 )
				stats.wins += 1;
			else if ( result == -1 )
				stats.losses += 1;
			else
				stats.ties += 1;	

			print_statistics( stats );

			if ( starter == 'X' )
				starter = 'O';
			else
				starter = 'X';
		}

    cout << "Bye now." << endl;
    return 0;
}

void print_statistics( Statistics & s ) {
	cout << "\n===== STATS =====\nWins:   " << s.wins << endl;
  cout << "Losses: " << s.losses << "\nTies:   " << s.ties << endl << endl;
}

void getSymbols( Pieces & symbols ) {
    char human;
    do {
        cout << endl << "Do you prefer X or O? ";
        if ( cin >> human ) {
            ;
        }
        else {
            cin.ignore();
        }
        cout << endl;

        if ( human == 'X' ) {
            symbols.human = 'X';
            symbols.computer = 'O';        
        }
        else if ( human == 'O' ) {
            symbols.human = 'O';
            symbols.computer = 'X';
        }
    } while ( (human != 'X') and (human != 'O') );

    cerr << "( symbols.human=" << symbols.human << " symbols.computer=" << symbols.computer << " )" << endl;
}

int gameLoop( Pieces & symbols, AiPlayer * cplayer, char starter ) {

    Board * board = new Board;
		board->setStarter( starter );

    cout << endl << ">>>>> Starting New Game <<<<<" << endl;
		cplayer->onNewGame();
    while ( true ) {
				if ( symbols.human == starter ) {
					board->cprint();
					cout << "Human: "     << symbols.human
							 << " Computer: " << symbols.computer
							 << " Starter: "  << starter << endl;
					int humanMove = getHumanMove( board );
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
					board->cprint();
					cout << "Human: "     << symbols.human
							 << " Computer: " << symbols.computer
							 << " Starter: "  << starter << endl;
					int humanMove = getHumanMove( board );
					board->intMove( symbols.human, humanMove );
					if ( board->hasWin() or board->isFull() )
						break;
				}
    }
    cout << "GAME OVER" << endl;
    board->cprint();
		if ( board->hasWin() ) {
			if ( board->getWinner() == symbols.human ) {
					cout << "Congratulations! You won!" << endl;
					cplayer->onLoss();
					return 1;
			}
			else if ( board->getWinner() == symbols.computer ) {
					cout << "Looks like you lose again. Too bad." << endl;
					cplayer->onWin();
					return -1;
			}
		}
		// not hasWin but isFull == tie
		if ( board->isFull() ) {
				cout << "It's a tie." << endl;
				cplayer->onTie();
				return 0;
		}
		cout << "Hmm. You shouldn't be seeing this message.\n" 
			<< "Check your program!" << endl;
		return 0;
}

int getHumanMove( Board * board ) {

	int moveCol, moveRow;
	bool validMove = false;

	do { // while ( not validMove )

		cout << "\nEnter your move:" << endl;

		do {
				cout << "  column (1-3): ";
				if ( cin >> moveCol ) {
						;
				}
				else {
						cin.clear();
						cin.ignore();
						cout << endl << "Your typing is incomprehensible to me. Enter a column between 1 and 3." << endl;
				}
		} while ( (moveCol < 1) or (moveCol > 3) );

		do {
				cout << "  row    (1-3): ";
				if ( cin >> moveRow ) {
						;
				}
				else {
						cin.clear();
						cin.ignore();
						cout << endl << "There's nothing I can do without an integer. Enter a row between 1 and 3." << endl;
				}
		} while ( (moveRow < 1) or (moveRow > 3) );

		moveRow -= 1; moveCol -=1;
		if ( board->isOccupied( moveCol, moveRow ) ) {
				cout << "I can't let you do that, Dave. That space is occupied." << endl;
		}
		else {
				validMove = true;
		}

	} while ( not validMove );

	return (moveRow * 3) + moveCol;
}


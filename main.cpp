#include <iostream>
#include <stdlib.h>
#include "Board.h"

using namespace ttt;

using std::cout;
using std::cerr;
using std::cin;
using std::endl;

const char * clearCmd = "clear";

struct Pieces {
    char human;
    char computer;
};    

void clearScreen( void );
void gameLoop( Pieces & );
void getSymbols( Pieces & );

int main() {
    Pieces symbols;
    getSymbols( symbols );
    gameLoop( symbols );
    cout << "Bye now." << endl;
    return 0;
}

void clearScreen() {
    system( clearCmd );
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

void gameLoop( Pieces & symbols ) {

    Board * board = new Board;
    board->cprint();
    cout << endl;
    
    cerr << "Starting gameLoop." << endl;

    cin.ignore();
    while ( not board->hasWin() ) {

        clearScreen();
        cout << endl;
        board->cprint();
        cout << "\nYour move:" << endl;

        int moveCol, moveRow;
        do {
            cout << "  column: ";
            if ( cin >> moveCol ) {
                ;
            }
            else {
                cin.clear();
                cin.ignore();
                cout << endl << "Your typing is incomprehensible to me. Enter a column between 1 and 3." << endl;
                board->cprint();
            }
        } while ( (moveCol < 1) or (moveCol > 3) );

        do {
            cout << "  row   : ";
            if ( cin >> moveRow ) {
                ;
            }
            else {
                cin.clear();
                cin.ignore();
                cout << endl << "There's nothing I can do without an integer. Enter a row between 1 and 3." << endl;
            }
        } while ( (moveRow < 1) or (moveRow > 3) );

        if ( board->isOccupied( moveCol-1, moveRow-1 ) ) {
            cout << "I can't let you do that, Dave. That space is occupied." << endl;
        }
        else {
            board->move( symbols.human, moveCol-1, moveRow-1 );
        }
    } // while ( not board->hasWin() )

    clearScreen();
    cout << " --- GAME OVER ---" << endl;
    board->cprint();
    if ( board->getWinner() == symbols.human )
        cout << "Congratulations! You won!" << endl;
    else
        cout << "Looks like you lose again. Too bad." << endl;
}


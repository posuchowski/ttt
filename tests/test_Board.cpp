#include <iostream>
#include "Board.h"

using namespace ttt;

using std::cout;
using std::cerr;
using std::endl;

int main() {

    Board * board = new Board;
    cout << "Created board object." << endl;
    board->cprint();

    board->set_X( 2 );
    cout << "Set bit 2 to X. Dump:" << endl;
    board->dump();
    cout << endl;
    board->cprint();

    board->set_O( 36 );
    cout << "Set O to 36. Dump:" << endl;
    board->dump();
    cout << endl;
    board->cprint();

    delete board;
    board = new Board;

    cout << "OK, new Board. Let's win." << endl;
    board->cprint();

    board->set_O( (7 << 6) );
    board->set_X( 2 + 4 + 16 );
    
    board->cprint();
    cout << "Checking win..." << endl;

    if ( board->hasWin() ) {
        cout << "\tSomebody won. It was... ";
        cout << board->getWinner() << endl;
    }
    else {
        cout << "\tNO WINNER!" << endl;
    }

}

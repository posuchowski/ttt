#include <iostream>
#include <math.h>
#include <stdlib.h>
#include "Board.h"

namespace ttt {

    using std::cout;
    using std::cerr;
    using std::endl;

    Board::Board() {
        X = O = 0;
        starter = winner = '\0';
        
        // Diagonals
        winConditions.push_back(
              1        +
            ( 1 << 4 ) +
            ( 1 << 8 ) 
        );
        winConditions.push_back(
            ( 1 << 2 ) +
            ( 1 << 4 ) +
            ( 1 << 6 )
        );

        for ( int c = 0; c < 9; c += 3 ) {
 
            // Row
            winConditions.push_back( pow(2,c) + pow(2,c+1) + pow(2,c+2) );

            // Column
            winConditions.push_back(
                pow(2,(c/3)) + pow(2,(c/3)+3) + pow(2,(c/3)+6)
            );

        }
        cerr << endl;
    }

		void Board::clear() {
				X = O = 0;
				starter = winner = '\0';
		}
    void Board::set_X( int x ) { X = x; }
		int  Board::get_X() 			 { return X; }
    void Board::set_O( int o ) { O = o; }
		int  Board::get_O() 			 { return O; }

		char Board::getStarter( void ) { return starter; }
    char Board::getWinner( void )  { return winner; }
		char Board::getMover( void )        { return mover; }

		void Board::setMover( char symbol ) { mover = symbol; }

		void Board::setStarter( char symbol ) {
			if ( starter == '\0' ) {
				std::cerr << "Setting Starter to " << symbol << std::endl;
				starter = mover = symbol;
			}
			else {
				throw( std::runtime_error( "Board::setStarter: starter already set!" ) );
			}
		}

    void Board::dump( void ) {
        cerr << "X: " << X << endl;
        cerr << "O: " << O << endl;
        cerr << "winConditions:" << endl;

        for ( std::vector<int>::iterator it = winConditions.begin();
              it != winConditions.end(); ++it ) {
            cerr << "\tint repr: " << *it << endl;
        }
        cerr << endl;
    }

    void Board::cprint( void ) {
        cout << endl;
        for ( int r = 0; r<3; ++r ) {
            cout << "\t";
            for ( int c = 0; c<3; ++c ) {
                (bool)(( X >> (r*3+c) ) & 1) ? cout << " X " :
                    (bool)(( O >> (r*3+c) ) & 1 ) ? cout << " O " :
                        cout << "   ";
                (bool)( ~c & 2 ) ? cout << "|" : cout << endl;
            }
            (bool)( ~r & 2 ) ? cout << "\t-----------" << endl : cout << endl;
        }
    }

    void Board::move( char symbol, int col, int row ) {
				intMove( symbol, row * 3 + col );
    }

		void Board::intMove( char symbol, int square ) {
				if ( symbol == 'X' )
						X = X | (1 << square);
				else
						O = O | (1 << square);
				history.push_back(square);
				mover = (mover == 'X') ? 'O' : 'X';
		}

    bool Board::isOccupied( int col, int row ) {
				return intIsOccupied(row * 3 + col);
		}

		bool Board::intIsOccupied( int square ) {
				if ( (X | O) & (1 << square) )
					return true;
				return false;
		}

		char Board::symbolAt( int col, int row ) {
				return intSymbolAt(row * 3 + col);
		}

		char Board::intSymbolAt( int square ) {
				if ( X & (1 << square ) )
					return 'X';
				if ( O & (1 << square ) )
					return 'O';
				return '\0';
		}

    bool Board::hasWin( void ) {
        for ( std::vector<int>::iterator it = winConditions.begin();
                it != winConditions.end(); ++it ) {
            if ( (X & *it) == *it ) {
                winner = 'X';
                return true;
            }
            if ( (O & *it) == *it ) {
                winner = 'O';
                return true;
            }
        }
        return false;
    }

} // namespace ttt

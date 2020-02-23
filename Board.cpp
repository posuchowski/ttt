#include <stdexcept>
#include <string>
#include <math.h>
#include <stdlib.h>
#include "Board.h"

namespace ttt {

		Board::Board() :
				X(0),
				O(0),
				boardFull( false ),
				gameWon( false ),
				gameTied( false ),
				locationX( 0 ),
				locationY( 0 ),
				starter('\0'),
				mover('\0'),
				winner('\0')
		{
			setWinConditions();
		}
				
    Board::Board( int locX, int locY ) :
				X(0),
				O(0),
				boardFull( false ),
				gameWon( false ),
				gameTied( false ),
				locationX( locX ),
				locationY( locY ),
				starter('\0'),
				mover('\0'),
				winner('\0')
		{
			setWinConditions();
		}

		// private
		
		void Board::setWinConditions() {
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
    }

    void Board::checkWin( void ) {
        for ( auto it = winConditions.begin(); it != winConditions.end(); ++it ) {
            if ( (X & *it) == *it ) {
								gameWon = true;
                winner = 'X';
            }
            if ( (O & *it) == *it ) {
								gameWon = true;
                winner = 'O';
            }
        }
    }

		void Board::checkFull( void ) {
			if ( (X | O) == 511 )
				boardFull = true;
		}

		void Board::checkBoard( void ) {
			checkWin();
			checkFull();
			if ( (hasWin() == false ) && (isFull() == true) ) {
					gameTied = true;
			}
		}

		// public
		
		void Board::clear() {
				X = O = 0;
				boardFull = gameWon = gameTied = false;
				starter = winner = mover = '\0';
		}

    void Board::set_X( int x ) {
			X = x;
			checkBoard();
		}

    void Board::set_O( int o ) {
			O = o;
			checkBoard();
		}

		int  Board::get_X() 			 { return X; }
		int  Board::get_O() 			 { return O; }

		char Board::getStarter( void ) { return starter; }
    char Board::getWinner( void )  { return winner; }

		char Board::getMover( void )        { return mover; }
		void Board::setMover( char symbol ) { mover = symbol; }

		bool Board::hasWin( void ) { return gameWon; }
		bool Board::hasTie( void ) { return gameTied; }
		bool Board::isFull( void ) { return boardFull; }

		void Board::setStarter( char symbol ) {
			if ( starter == '\0' ) {
				starter = mover = symbol;
			}
			else {
				throw( std::runtime_error( "Board::setStarter: starter already set!" ) );
			}
		}

		std::string Board::toString( void ) {
				std::string repr = "---------";
				for ( int i=0; i<9; i++ ) {
					if ( (X >> i) & 1 ) {
						repr.replace( i, 1, 1, 'X' );
					}
					else if ( (O >> i) & 1 ) {
						repr.replace( i, 1, 1, 'O' );
					}
				}
				return repr;
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
				checkBoard();
		}

		void Board::undoMove() {
			int square = history.back();
			if ( mover == 'X' ) {
				mover = 'O';
				undoMoveO( square );
			}
			else {
				mover = 'X';
				undoMoveX( square );
			}
			history.pop_back();
		}

		void Board::undoMoveX( int square ) {
			set_X( get_X() - (1 << square) );
		}

		void Board::undoMoveO( int square ) {
			set_O( get_O() - (1 << square) );
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

		int Board::getLastMove( void ) {
			if ( history.size() > 0 )
				return history[history.size()-1];
			return -1;
		}

} // namespace ttt


#include <vector>
#include <iostream>
#include <random>
#include <time.h>
#include "AiPlayer.h"

namespace ttt {

		AiPlayer::AiPlayer() {
			memory = new Memory;
		}

		void AiPlayer::clearPossibleMoves() {
			possibleMoves.clear();
			highestScore = 0;
		}

		void AiPlayer::dumpMoveScores( std::string msg ) {
			std::cerr << "AiPlayer: Move Scores " << msg << ":" << std::endl;
			for ( AiMove * m : possibleMoves ) {
				std::cerr << "\t" << m->move << " = " << m->score << std::endl;
			}
			std::cerr << "Highest Score is " << highestScore << std::endl;
			std::cerr << "---" << std::endl;
		}

		void AiPlayer::scoreMovesFromMemory() {
			for ( AiMove * m : possibleMoves ) {
				m->score += memory->scoreMove(m->move);
			}
		}

		void AiPlayer::findHighestScore() {
			highestScore = possibleMoves[0]->score;
			for ( AiMove * m : possibleMoves ) {
				if ( m->score > highestScore )
					highestScore = m->score;
			}
		}

		/*
  		 Just iterating and calling vector::erase won't work,
		   due to the end of the vector being altered. The beginning
			 is sound, so we just start where we left off before erase.
		
		   FIXME: Is there a more efficient way to do this?
				      (Although the size is quite small, this is show code.)
		*/
		void AiPlayer::dropLowerThanHighest() {
			std::vector<AiMove *>::iterator it, last = possibleMoves.begin();
			bool erased = true;
			while ( (erased = true) and (last != possibleMoves.end()) ) {
				erased = false; it = last;
				while ( (erased == false) and  (it != possibleMoves.end()) ) {
					if ( (*it)->score < highestScore ) {
						possibleMoves.erase(it);
						erased = true;
					}
					else {
						last = ++it;
					}
				}
			}
		}

		void AiPlayer::scoreObviousWinsAndBlocks(Board * actual) {
			Board * playBoard = new Board;
			playBoard->set_X( actual->get_X() );
			playBoard->set_O( actual->get_O() );
			char mySymbol  = actual->getMover();
			char itsSymbol = (mySymbol == 'X') ? 'O' : 'X';

			for ( AiMove * m : possibleMoves ) {
				playBoard->intMove(mySymbol, m->move);
				if ( playBoard->hasWin() == true ) {
					m->score = 999;
				}
				mySymbol == 'X' ? playBoard->undoMoveX( m->move )
												: playBoard->undoMoveO( m->move );

				playBoard->intMove(itsSymbol, m->move);
				if ( playBoard->hasWin() == true ) {
					m->score = 666;
				}
				itsSymbol == 'X' ? playBoard->undoMoveX( m->move )
												 : playBoard->undoMoveO( m->move );
			}
		}

		void AiPlayer::collectEmptySquares(Board * board) {
			clearPossibleMoves();
			for ( int i=0; i<9; i++ ) {
				if ( ! board->intIsOccupied( i ) ) {
					//std::cerr << "AiPlayer: adding empty square " << i << std::endl;
					possibleMoves.push_back(
						new AiMove { i, 0 }
					);
				}
			}
		}

		void AiPlayer::dumpPossibleMoves() {
			std::cerr << "AiPlayer: possibleMoves: ";
			for ( AiMove * move : possibleMoves ) {
				std::cerr << move->move << " ";
			}
			std::cerr << std::endl;
		}

		const std::vector<AiMove *>& AiPlayer::getPossibleMoves() {
			return possibleMoves;
		}

		int AiPlayer::returnRandomMove() {
			// std::cerr << "AiPlayer:: choosing between " << possibleMoves.size() << " moves..." << std::endl;
			srand( time(NULL) );
			int r = rand() % possibleMoves.size();
			// std::cerr << "AiPlayer: returning move #" << r << std::endl;
			return possibleMoves[r]->move;
		}

    int AiPlayer::makeMove(Board * board) {

			int opponentsMove = board->getLastMove();
			if ( opponentsMove > -1 ) {
				// std::cerr << "AiPlayer: opponents move was " << opponentsMove << std::endl;
				memory->advance(opponentsMove);
			}

			collectEmptySquares(board);
			scoreObviousWinsAndBlocks(board);
			findHighestScore();
			dropLowerThanHighest();

			int move;
			if ( possibleMoves.size() > 1 ) {
				scoreMovesFromMemory();
				findHighestScore();
				dropLowerThanHighest();
				move = returnRandomMove();
			}
			else {
				move = possibleMoves[0]->move;
			}

			dumpMoveScores( "(FINAL)" );
			// std::cerr << "AiPlayer: advancing move " << move << std::endl;
			memory->advance( move );
			return move;
    }

		void AiPlayer::onNewGame() {
			memory->resetMovePtr();
		}

		void AiPlayer::onLoss() {
			memory->rememberLoss();
		}

		void AiPlayer::onWin() {
			memory->rememberWin();
		}

		void AiPlayer::onTie() {
			memory->rememberTie();
		}

}


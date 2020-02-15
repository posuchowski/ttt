#pragma once
#include <vector>

namespace ttt {

    class Board {

        private:
            int X, O;
						bool boardFull, gameWon, gameTied;
						// location on the Big Board:
						int locationX, locationY; 
            char starter, mover, winner;
            std::vector<int> winConditions;
						std::vector<int> history;

						void setWinConditions(void);
						void checkWin(void);
						void checkFull(void);
						void checkBoard(void);

        public:
            Board();
						Board(int, int);
						void clear(void);
            void set_X(int);
						int  get_X(void);
            void set_O(int);
						int  get_O(void);

						char getStarter(void);
            char getWinner(void);

						char getMover(void);
						void setMover(char);

            bool hasWin(void);
						bool hasTie(void);
						bool isFull(void);

						void setStarter(char);

            void dump(void);
            void cprint(void);

            void move(char, int, int);
						void intMove(char, int);
						void undoMove(void);
						void undoMoveX(int);
						void undoMoveO(int);
            bool isOccupied(int, int);
						bool intIsOccupied(int);
						char symbolAt(int, int);
						char intSymbolAt(int);
						int getLastMove(void);

    }; // class Board

} // namespace ttt


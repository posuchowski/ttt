#pragma once
#include <vector>

namespace ttt {

    class Board {

        private:
            int X, O;
            char starter, mover, winner;
            std::vector<int> winConditions;
						std::vector<int> history;

        public:
            Board();
						void clear(void);
            void set_X(int);
						int get_X(void);
            void set_O(int);
						int get_O(void);

						void setMover(char);
						char getMover(void);
						void setStarter(char);
						char getStarter(void);
            char getWinner(void);

            void dump(void);
            void cprint(void);

            void move(char, int, int);
            bool isOccupied(int, int);
						char symbolAt(int, int);
            bool hasWin(void);

    }; // class Board

} // namespace ttt


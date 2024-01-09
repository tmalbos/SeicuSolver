#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <list>

using namespace std;

const short directions[4][2] = {{- 2, 0}, {0, - 2}, {0, 2}, {2, 0}};
struct movement{
    short x_coord;
    short y_coord;
    short direction[2];
};

class Board {
    public:
        Board();

        bool moveToken(short x, short y, const short direction[2]);
        bool undoMove();

        void printBoard() const;
        bool gameOver() const;
        bool win() const;
        bool canMove(short x, short y, const short direction[2]) const;
        bool isValid(short x, short y) const;
        bool isEmpty(short x, short y) const;
        bool isOccupied(short x, short y) const;
        list<movement> getSolution() const;

    private:
        static const int SIZE = 7;
        short board[SIZE][SIZE];
        list<movement> solution;
};

#endif // BOARD_H

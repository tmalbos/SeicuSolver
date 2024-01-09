#include "Board.h"

Board::Board(){
    for (short i = 0; i < SIZE; ++i)
        for (short j = 0; j < SIZE; ++j) {
            if ((((i + 2) % SIZE) > (SIZE / 2) || ((j + 2) % SIZE) > (SIZE / 2)) &&
                (i != SIZE / 2 || j != SIZE / 2))
                this -> board[i][j] = 1;
            else if (i != SIZE / 2 && j != SIZE / 2)
                this -> board[i][j] = -1;
            else
                this -> board[i][j] = 0;
        }
}


bool Board::moveToken(short x, short y, const short direction[2]){
    if (canMove(x, y, direction)){
        this -> board[x][y] = 0;
        this -> board[x + direction[0]][y + direction[1]] = 1;
        this -> board[x + direction[0] / 2][y + direction[1] / 2] = 0;
        movement new_move;
        new_move.x_coord = x;
        new_move.y_coord = y;
        new_move.direction[0] = direction[0];
        new_move.direction[1] = direction[1];
        this -> solution.push_back(new_move);
        return true;
    }
    return false;
}

bool Board::undoMove(){
    if (!this -> solution.empty()){
        movement last_move = this -> solution.back();
        short x = last_move.x_coord;
        short y = last_move.y_coord;
        short direction[2];
        direction[0] = last_move.direction[0];
        direction[1] = last_move.direction[1];

        this -> board[x + direction[0] / 2][y + direction[1] / 2] = 1;
        this -> board[x + direction[0]][y + direction[1]] = 0;
        this -> board[x][y] = 1;
        this -> solution.pop_back();
        return true;
    }
    return false;
}

void Board::printBoard() const {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (this -> board[i][j] == -1)
                cout << "   ";
            else if (this -> board[i][j] == 0)
                cout << " O ";
            else if ((i + j) % 2 == 0)
                cout << " G ";
            else
                cout << " W ";
        }

        cout << '\n';
    }
}

bool Board::gameOver() const{
}

bool Board::win() const{
    if (this -> solution.size() == 31 && this -> board[3][3] == 1)
        return true;
    return false;
}

bool Board::canMove(short x, short y, const short direction[2]) const{
    short nueva_x = x + direction[0];
    short nueva_y = y + direction[1];

    if (isValid(x, y) &&
        isOccupied(x, y) &&
        isValid(nueva_x, nueva_y) &&
        isEmpty(nueva_x, nueva_y) &&
        isOccupied(x + direction[0] / 2, y + direction[1] / 2))
        return true;

    return false;
}

bool Board::isValid(short x, short y) const{
    if (x >= 0 && x < 7 && y >= 0 && y < 7)
        if (this -> board[x][y] != - 1)
            return true;
    return false;
}

bool Board::isEmpty(short x, short y) const{
    if (this -> board[x][y] == 0)
        return true;
    return false;
}

bool Board::isOccupied(short x, short y) const{
    if (this -> board[x][y] == 1)
        return true;
    return false;
}

list<movement> Board::getSolution() const{
    return this -> solution;
}

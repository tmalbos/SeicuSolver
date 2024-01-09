#include <iostream>
#include <list>

#include "Board.h"
#include "Token.h"

using namespace std;

bool Backtracking(Board state, list<movement> & solve, bool player){
    if (state.win()){
        cout << "\t Se gano el juego\n\n";
        solve = state.getSolution();
        return true;
    }
    else{
        bool found = false;
        for (short i = 0; !found && i < 7; i++)
            for (short j = 0; !found && j < 7; j++)
                for (short k = 0; !found && k < 4; k++)
                    if ((i + j) % 2 == player && state.canMove(i, j, directions[k])){
                        state.moveToken(i, j, directions[k]);
                        found = Backtracking(state, solve, !player);
                        if (!found)
                            state.undoMove();
                    }
        return found;
    }
}

void printSolution(list<movement> solution){
    list<movement>::iterator mi = solution.begin();
    cout << "\n";
    for (mi; mi != solution.end(); mi++){
        cout << "\n|> (" << mi -> x_coord << ", " << mi -> y_coord << ") ";
        if (mi -> direction[0] == - 2)
            cout << "up";
        else if (mi -> direction[1] == - 2)
            cout << "left";
        else if (mi -> direction[1] == 2)
            cout << "right";
        else
            cout << "down";
    }
}

int main(){
    Board board;
    list<movement> solve;
    board.printBoard();
    Backtracking(board, solve, 0);
    printSolution(solve);
    return 0;
}

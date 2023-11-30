#ifndef GAME_H
#define GAME_H

#include "chessboard.h"

class Game
{
public:
    Game(ChessBoard* chessboard);

    void makeMove(int fromRow, int fromCol, int toRow, int toCol);
private:
    ChessBoard* chessboard;
    ChessPiece::Color currentPlayer;
};

#endif // GAME_H

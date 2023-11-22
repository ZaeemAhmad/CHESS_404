#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "chesspiece.h"

class ChessBoard
{
public:
    ChessBoard();

    void initialBoard();
    void movePiece(int fromRow, int fromCol, int toRow, int toCol);
    bool isSquareOccupied(int row, int col) const;
    const ChessPiece& getPiece(int row, int col) const;

private:
    ChessPiece board[8][8];
};

#endif // CHESSBOARD_H

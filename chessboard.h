#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "chesspiece.h"

class ChessBoard :public ChessPiece
{
public:
    ChessBoard();

    void initialBoard();

    // Piece Movement Logic
    void movePiece(int fromRow, int fromCol, int toRow, int toCol);
    bool isSquareOccupied(int row, int col) const;

    // To check if the given coordinates are between 8x8
    bool isValidChessSquare(int row, int col) const;

    // Getters
    const ChessPiece& getPiece(int row, int col) const;
  /*  ChessPiece::*/Color getPieceColor(int row, int col) const;
  /*  ChessPiece::*/Type getPieceType(int row, int col) const;

private:
    ChessPiece board[8][8];
};

#endif // CHESSBOARD_H

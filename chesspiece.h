#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <QString>

class ChessBoard;

class ChessPiece
{
public:
    enum Type { King, Queen, Bishop, Knight, Rook, Pawn, Empty };
    enum Color { White, Black, NONE };

    ChessPiece(Type type = Empty, Color color = NONE);
    Type getType() const;
    Color getColor() const;

    bool isEmpty() const;

    bool isValidMove(Type type, int fromRow, int fromCol, int toRow, int toCol, const ChessBoard& board) const;
    bool isValidCapture(int fromRow, int fromCol, int toRow, int toCol, const ChessBoard& board) const;
private:
    Type type;
    Color color;
};

#endif // CHESSPIECE_H

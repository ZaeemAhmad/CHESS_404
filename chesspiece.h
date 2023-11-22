#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <QString>

class ChessPiece
{
public:
    enum Type { King, Queen, Bishop, Knight, Rook, Pawn,Empty };
    enum Color { White, Black };


    ChessPiece(Type type = Queen, Color color = White);
//  ChessPiece(Type type = Pawn, Color color = White);
    Type getType() const;
    Color getColor() const;

    bool isEmpty() const;

    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol);
    bool isValidCapture(int fromRow, int fromCol, int toRow, int toCol);
private:
    Type type;
    Color color;
};

#endif // CHESSPIECE_H
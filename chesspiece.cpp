#include "chesspiece.h"

ChessPiece::ChessPiece(Type type, Color color) : type(type), color(color) {}

ChessPiece::Type ChessPiece::getType() const
{
    return type;
}

ChessPiece::Color ChessPiece::getColor() const
{
    return color;
}

bool ChessPiece::isEmpty() const
{
    return (type == Empty );
}

bool ChessPiece::isValidMove(int fromRow, int fromCol, int toRow, int toCol)
{
    // Validation here
    return true;
}

bool ChessPiece::isValidCapture(int fromRow, int fromCol, int toRow, int toCol)
{
    // Valid capture logic here

    return true;
}







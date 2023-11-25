#include "chesspiece.h"
#include <QDebug>

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
    return ( type == Empty );
}

bool ChessPiece::isValidMove(Type type, Color color, int fromRow, int fromCol, int toRow, int toCol) const
{
    const int rowDiff = fromRow - toRow;
    const int colDiff = fromCol - toCol;

    qDebug() << type << color;
    if(type == Rook){
        // A Rook can move horizontal & Vertical
        if(color == White){
            // From Row: 7 to 0 & Col: 0 to 7

        }else{
            // From Row: 0 to 7 & Col: 7 to 0
        }
    }
    return true;
}

bool ChessPiece::isValidCapture(Type type, Color color,int fromRow, int fromCol, int toRow, int toCol)
{
    // Valid capture logic here

    return true;
}

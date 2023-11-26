#include "chesspiece.h"
#include "chessboard.h"
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

bool ChessPiece::isValidMove(Type type, int fromRow, int fromCol, int toRow, int toCol, const ChessBoard& board) const
{
    const int rowDiff = fromRow - toRow;
    const int colDiff = fromCol - toCol;
    int i;

    ChessPiece piece = board.getPiece(fromRow, fromCol);

    if(type == Rook){
        qDebug() << "Inside";
        if(fromRow == toRow && fromCol == toCol)
            return false; // Case when the piece is dropped at same location

        // A Rook can move horizontal & Vertical

        // Colision detection
        // From Row: 7 to 0 & Col: 0 to 7
        if(fromRow == toRow){
            // Moved Horizontally

            if(fromCol < toCol){
                // Move right
                for(i = fromCol + 1; i <= toCol; i++){
                    if(!board.getPiece(fromRow, i).isEmpty())
                        return isValidCapture(fromRow, i, toRow, toCol, board);
                }
            } else {
                // Move left
                for(i = fromCol - 1; i >= toCol; i--){
                    if(!board.getPiece(fromRow, i).isEmpty())
                        return isValidCapture(fromRow, i, toRow, toCol, board);
                }
            }
        } else if (fromCol == toCol){
            // Vertical Move
            if(fromRow < toRow){
                // Move down
                for(i = fromRow + 1; i <= toRow; i++){
                    if(!board.getPiece(i, fromCol).isEmpty())
                        return isValidCapture(i, fromCol, toRow, toCol, board);
                }
            } else {
                // Move up
                for(i = fromRow - 1; i >= toRow; i--){
                    if(!board.getPiece(i, fromCol).isEmpty())
                        return isValidCapture(i, fromCol, toRow, toCol, board);
                }
            }
        } else {
            // Not a valid move
            return false;
        }

    }
    return true;
}

bool ChessPiece::isValidCapture(int fromRow, int fromCol, int toRow, int toCol, const ChessBoard &board) const
{
    // Valid capture logic here
    if(!board.isValidChessSquare(toRow, toCol))
        return false;

    ChessPiece piece = board.getPiece(fromRow, fromCol);
    ChessPiece nextPiece = board.getPiece(toRow, toCol);

    return !nextPiece.isEmpty() && nextPiece.getColor() == piece.getColor();
}

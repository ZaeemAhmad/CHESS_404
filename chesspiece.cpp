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


bool ChessPiece::isValidMove_Rook(Type type, int fromRow, int fromCol, int toRow, int toCol, const ChessBoard& board) const
{
    int i;

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
                for(i = fromCol + 1; i < toCol; i++){
                    if(!board.getPiece(fromRow, i).isEmpty())
                        return isValidCapture(fromRow, fromCol, toRow, toCol, board);
                }
            } else {
                // Move left
                for(i = fromCol - 1; i > toCol; i--){
                    if(!board.getPiece(fromRow, i).isEmpty())
                        return isValidCapture(fromRow, fromCol, toRow, toCol, board);
                }
            }
        } else if (fromCol == toCol){
            // Vertical Move
            if(fromRow < toRow){
                // Move down
                for(i = fromRow + 1; i < toRow; i++){
                    if(!board.getPiece(i, fromCol).isEmpty())
                        return isValidCapture(fromRow, fromCol, toRow, toCol, board);
                }
            } else {
                // Move up
                for(i = fromRow - 1; i > toRow; i--){
                    if(!board.getPiece(i, fromCol).isEmpty())
                        return isValidCapture(fromRow, fromCol, toRow, toCol, board);
                }
            }
        } else {
            // Not a valid move
            return false;
        }

    }
    return true;
}
bool ChessPiece::isValidMove_King(Type type,int fromRow, int fromCol, int toRow, int toCol, ChessBoard& board) const
{
    if (type == King) {
        qDebug() << "Inside King";

        // Check if the destination is the same as the source
        if (fromRow == toRow && fromCol == toCol)
            return false;

        // King can move one square in any direction (horizontal, vertical, or diagonal)
        int rowDiff = qAbs(toRow - fromRow);
        int colDiff = qAbs(toCol - fromCol);

        if ((rowDiff == 1 && colDiff == 0) ||  // Vertical move
            (rowDiff == 0 && colDiff == 1) ||  // Horizontal move
            (rowDiff == 1 && colDiff == 1))    // Diagonal move
        {
            // Check for collision with other pieces
            if (!board.getPiece(toRow, toCol).isEmpty()) {
                // Capture the piece at the destination and delete the piece
                board.removePiece(toRow, toCol);
            }

            return true;
        }
    }

    // Not a valid move for the King
    return false;
}

bool ChessPiece::isValidCapture(int fromRow, int fromCol, int toRow, int toCol, const ChessBoard &board) const
{
    // Valid capture logic here
    if(!board.isValidChessSquare(toRow, toCol))
        return false;

    ChessPiece piece = board.getPiece(fromRow, fromCol);
    ChessPiece nextPiece = board.getPiece(toRow, toCol);

    return (nextPiece.getColor() == piece.getColor());
}

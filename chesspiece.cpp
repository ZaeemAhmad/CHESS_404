#include "chesspiece.h"
#include "chessboard.h"
#include <QDebug>
#include<iostream>
ChessPiece::ChessPiece(Type type, Color color) : type(type), color(color) {}

ChessPiece::Type ChessPiece::getType() const
{
    return type;
}

ChessPiece::Color ChessPiece::getColor() const
{
    return color;
}

void ChessPiece::setType(Type t)
{
    type = t;
}

bool ChessPiece::isEmpty() const
{
    return ( type == Empty );
}

// Validation code all pieces

bool ChessPiece::isValidMove_Rook(Type type, int fromRow, int fromCol, int toRow, int toCol, const ChessBoard& board) const
{
    int i;

    if(type == Rook){
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
        // Check if the destination is the same as the source
        if (fromRow == toRow && fromCol == toCol)
            return false;

        // King can move one square in any direction (horizontal, vertical, or diagonal)
        int rowDiff = qAbs(toRow - fromRow);
        int colDiff = qAbs(toCol - fromCol);
        qDebug() << qAbs(toRow - fromRow) << (toRow - fromRow);

        qDebug() << board.getPieceType(fromRow, fromCol) << board.getPieceType(toRow, toCol);
        if ((rowDiff == 1 && colDiff == 0) ||  // Vertical move
            (rowDiff == 0 && colDiff == 1) ||  // Horizontal move
            (rowDiff == 1 && colDiff == 1))    // Diagonal move
        {
            return true;
        }
    }

    // Not a valid move for the King
    return false;
}


bool ChessPiece::isValidMove_Pawn( int fromRow, int fromCol, int toRow, int toCol, const ChessBoard& board) const
{
    int rowDiff=toRow-fromRow, colDiff=toCol-fromCol;
    if ( board.getPieceColor(fromRow,fromCol)==Black && colDiff==0)//check if piece is black and moving stright or not.
    {
        if (rowDiff==1)//check if piece is moving only one square
        {
            if (!board.isSquareOccupied(toRow,toCol))// check if destination square is occupied or not.
                return true;
        }
        else if (rowDiff==2 && fromRow==1)// check if piece is moving 2 squares from initial position.
        {
            if (!board.isSquareOccupied(toRow,toCol) && !board.isSquareOccupied(fromRow + 1, fromCol))
                return true;
        }
    }
    else if ( board.getPieceColor(fromRow,fromCol)==White && colDiff==0)//check if white and moving stright or not.
    {
        if (rowDiff == -1)//check if piece is moving only one square
        {
            if (!board.isSquareOccupied(toRow,toCol))// check if destination square is occupied or not.
                return true;
        }
        else if (rowDiff==-2 && fromRow==6)// check if piece is moving 2 squares from initial position.
        {
            if (!board.isSquareOccupied(toRow,toCol) && !board.isSquareOccupied(fromRow - 1, fromCol))
                return true;
        }
    }
    // Diagonal capture conditions.
    else if ((colDiff == 1 || colDiff == -1) && rowDiff == 1 &&
             board.getPieceColor(fromRow,fromCol) == Black &&
             board.isSquareOccupied(toRow,toCol))
    {
        return true;
    }
    else if ((colDiff == 1 || colDiff == -1) && rowDiff == -1 &&
             board.getPieceColor(fromRow,fromCol)==White &&
             board.isSquareOccupied(toRow,toCol))
    {
        return true;
    }

    return false;
}

bool ChessPiece::isValidMove_Knight(int fromRow, int fromCol, int toRow, int toCol, const ChessBoard &board) const
{
    // Knight logic
    // Night moves in L pattern

    // Move up-left (two row up one left)
    // Move up-right (two row up one right)
    // Move bottom-left (two row down one left)
    // Move bottom-right (two row down one right)
    if(fromRow == toRow && fromCol == toCol)
        return false;

    int rowDiff = (toRow > fromRow) ? (toRow - fromRow) : (fromRow - toRow);
    int colDiff = (toCol > fromCol) ? (toCol - fromCol) : (fromCol - toCol);

    if ((rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2)){
        // Valid Knight Move
        return true;
    }

    return false;
}

bool ChessPiece::isValidMove_Bishop( int fromRow, int fromCol, int toRow, int toCol, const ChessBoard& board) const
{
    int rowDiff=toRow-fromRow, colDiff=toCol-fromCol;
    int RowDiff_positive=(rowDiff<0)?(rowDiff*-1):(rowDiff),ColDiff_positive=(colDiff<0)?(colDiff*-1):(colDiff);
    if ( RowDiff_positive == ColDiff_positive)
    {
        if (rowDiff>0 && colDiff>0)
        {
            for (int i=fromRow+1,j=fromCol+1; i<toRow && j<toCol; i++,j++)
            {
                if (board.isSquareOccupied(i,j))
                {
                    return false;
                }
            }
            return true;
        }
        else if (rowDiff<0 && colDiff<0)
        {
            for (int i=fromRow-1, j=fromCol-1; i>toRow && j>toCol; i--, j-- )
            {
                if(board.isSquareOccupied(i,j))
                {
                    return false;
                }
            }
            return true;
        }
        else if (rowDiff<0 && colDiff>0)
        {
            for (int i=fromRow-1, j=fromCol+1; i>toRow && j<toCol; i--, j++ )
            {
                if (board.isSquareOccupied(i,j))
                {
                    return false;
                }
            }
            return true;
        }
        else if (rowDiff>0 && colDiff<0)
        {
            for (int i=fromRow+1 ,j=fromCol-1; i<toRow && j>toCol; i++,j-- )
            {
                if (board.isSquareOccupied(i,j))
                {
                    return false;
                }
            }
            return true;
        }
    }
        return false;
}

// isValidCapture returns true if colors are same.
bool ChessPiece::isValidCapture(int fromRow, int fromCol, int toRow, int toCol, const ChessBoard &board) const
{
    // Valid capture logic here
    if(!board.isValidChessSquare(toRow, toCol))
        return false;

    ChessPiece piece = board.getPiece(fromRow, fromCol);
    ChessPiece nextPiece = board.getPiece(toRow, toCol);
    return (nextPiece.getColor() == piece.getColor());
}

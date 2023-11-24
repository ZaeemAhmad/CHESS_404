#include "chessboard.h"
#include <QDebug>
ChessBoard::ChessBoard()
{
    initialBoard();
}

void ChessBoard::initialBoard()
{
    // Initial Board logic (Connection with gui here)
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if (row == 0 || row == 7) {
                // Setup row with black and white pieces
                ChessPiece::Color color = (row == 0) ? ChessPiece::Color::Black : ChessPiece::Color::White;
                ChessPiece::Type type;

                switch (col) {
                case 0:
                case 7:
                    type = ChessPiece::Type::Rook;
                    break;
                case 1:
                case 6:
                    type = ChessPiece::Type::Knight;
                    break;
                case 2:
                case 5:
                    type = ChessPiece::Type::Bishop;
                    break;
                case 3:
                    type = ChessPiece::Type::Queen;
                    break;
                case 4:
                    type = ChessPiece::Type::King;
                    break;
                default:
                    type = ChessPiece::Type::Pawn;
                    break;
                }

                board[row][col] = ChessPiece(type, color);
            }
            else if (row == 1 || row == 6) {
                // Placing pawns
                ChessPiece::Color color = (row == 1) ? ChessPiece::Color::Black : ChessPiece::Color::White;
                qDebug() << "At row: " << row << " Color: " << color;
                ChessPiece::Type type = ChessPiece::Type::Pawn;
                board[row][col] = ChessPiece(type, color);
            } else
            {
                // Empty Squares in the middle
                 ChessPiece::Type type = ChessPiece::Type::Empty;
                board[row][col] = ChessPiece(type);
            }
        }
    }
}

void ChessBoard::movePiece(int fromRow, int fromCol, int toRow, int toCol)
{
    // Chess Move implementation logic
    // Checking if the move is valid before upadating the board
    if(isValidChessSquare(fromRow, fromCol) &&
        isValidChessSquare(toRow, toCol)){

        const ChessPiece::Color currentPositionPiece = getPieceColor(fromRow, fromCol);
        const ChessPiece::Color nextPositionPiece = getPieceColor(toRow, toCol);

        if(currentPositionPiece != nextPositionPiece){
            ChessPiece pieceToMove = board[fromRow][fromCol];
            // firstly changing the current board location as empty
            board[fromRow][fromCol] = ChessPiece(); // Initialize the current piece to default constructor
            // Now updating the piece location
            board[toRow][toCol] = pieceToMove;
        }
    }

}

bool ChessBoard::isSquareOccupied(int row, int col) const
{
    // Returns Truthy or Falsy based on if the current square is taken or not
    return false;
}

bool ChessBoard::isValidChessSquare(int row, int col) const
{
    return (row >= 0 && row < 8 && col >= 0 && col < 8);
}

const ChessPiece &ChessBoard::getPiece(int row, int col) const
{
    // Returns the piece reference at current row & col
    if(row >= 0 && row < 8 && col >=0 && col < 8){
        return board[row][col];
    } else {
        // Return an empty chess piece if the row and col are out of bound
        return ChessPiece();
    }
}

ChessPiece::Color ChessBoard::getPieceColor(int row, int col) const
{
    if(row >= 0 && row < 8 && col >= 0 && col < 8){
        ChessPiece::Color pieceColor = board[row][col].getColor();
        return pieceColor;
    }else{
        return ChessPiece::Color::NONE;
    }
}


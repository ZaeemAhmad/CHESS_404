#include "game.h"

Game::Game(ChessBoard* chessboard) : chessboard(chessboard)
{
    chessboard->initialBoard();
    currentPlayer = ChessPiece::White;
}

void Game::makeMove(int fromRow, int fromCol, int toRow, int toCol)
{
    ChessPiece pieceToMove = chessboard->getPiece(fromRow, fromCol);

    if(!pieceToMove.isEmpty() && pieceToMove.getColor() == currentPlayer){
        // Check if the move is valid
        if(chessboard->VALIDMOVE(pieceToMove.getType(), fromRow, fromCol, toRow, toCol)){
            chessboard->movePiece(fromRow, fromCol, toRow, toCol);
            // Switches the turn
            currentPlayer = (currentPlayer == ChessPiece::Color::White) ? ChessPiece::Color::Black : ChessPiece::Color::White;
        }
    }
}
